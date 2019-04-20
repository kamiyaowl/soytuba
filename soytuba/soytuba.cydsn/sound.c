#include "sound.h"

// マルチスレッドにするならQueueに積む際にDCacheFlushしよう
static average_t slider_average = {};
static average_t pressure_average[SHARED_MEM_PRESSURE_N] = {};

//  入力値の移動平均を計算します
uint32_t average(uint32_t src, average_t* ave) {
    // dequeue分を引き算する
    ave->sum = (ave->sum > ave->buf[ave->ptr]) ? (ave->sum - ave->buf[ave->ptr]) : 0;
    // データ追記
    ave->buf[ave->ptr] = src;
    ave->sum += src; // 今回の値を加算
    ave->ptr = (ave->ptr < SOUND_AVERAGE_N - 2) ? (ave->ptr + 1) : 0;
    // 結果を返す
    ave->dst = ave->sum / SOUND_AVERAGE_N;

    return ave->dst;
}
// Queueから使える領域をもらえるまでまつ
sound_command_t* alloc_sound_control() {
    sound_command_t* ptr;
    // もしマルチスレッドにするなら、確保できない間はスキップするかRTOSのDelayで実装すべき
    do {
        ptr = queue_get_enqueue_ptr();
    } while(ptr == 0); // == NULL
    return ptr;
}
void sound_init() {
    // default setting
    // TODO: 領域は現物で変更可能性が高い
    shared_mem.sound_setting.slider_low_limit = 0x100;
    shared_mem.sound_setting.slider_high_limit = 0x0f00;
    shared_mem.sound_setting.acc_tapping_mode_y = 3000; // 4096で1G
}
void sound_update() {
    // control allocate
    sound_command_t* control = alloc_sound_control();

    /***** ADC入力値アベレージング (range外でもやっておかないと値が突然飛ぶ) *****/
    // ADCの値は何もしてなければ最大値で反転しているので注意
    uint32_t slider    = average(shared_mem.adc_slider     , &slider_average);
    uint32_t pressure0 = average(shared_mem.adc_pressure[0], &pressure_average[0]);
    uint32_t pressure1 = average(shared_mem.adc_pressure[1], &pressure_average[1]);
    uint32_t pressure2 = average(shared_mem.adc_pressure[2], &pressure_average[2]);
    // 圧力選択(一番小さい値を採用)
    uint32_t pressure = ((pressure1 < pressure2) ? 
            ((pressure0 < pressure1) ? pressure0 : pressure1):
            ((pressure0 < pressure2) ? pressure0 : pressure2)
        ); // は、何この可読性の低いゴミコード
    // ADC12bit(inverted) -> 音量5bit 適当に丸める
    uint8_t vol = ((~(pressure >> 7)) & 0x1f);
    uint8_t vol_valid = vol > 0;
    // スライダの有効判定は、アベレージング以前の即値で行う(Issue #7)
    uint8_t slider_valid =  ((shared_mem.adc_slider > shared_mem.sound_setting.slider_low_limit) &&
                             (shared_mem.adc_slider < shared_mem.sound_setting.slider_high_limit));
    // 下方向を向いていたら(+現在トリガを引いていなければ) タッピングモードに切り替える
    uint8_t is_tapping = ((!vol_valid) && shared_mem.acc[1] > shared_mem.sound_setting.acc_tapping_mode_y) ? 1 : 0;


    /***** Commanbd生成 *****/
    if (slider_valid) {
        shared_mem.has_keyon = 0x1;
        // 遅いけど音階選択
        float ratio = (slider - shared_mem.sound_setting.slider_low_limit) / (float)(shared_mem.sound_setting.slider_high_limit - shared_mem.sound_setting.slider_low_limit);
        uint32_t pitch_index = (uint32_t)(ratio * PITCH_TABLE_N); // Accで増減するのでまだテーブルは引かない
        //TODO: IMU Table shift

        pitch_t p = PITCH_TABLE[pitch_index];

        if (is_tapping) {
            shared_mem.tapping = 0x1;
            // sliderの触った場所で即時音を出す。音量はvol依存。Note OffはSlider依存
            control->keyon = 0x1;
            control->interpolation = 0x1;
            control->block = p.block;
            control->fnum = p.fnum;
            control->vovol = 0x54; // volによらずに適当に出す
        } else {
            // volの値に応じて音を出す。sliderの位置で音階は遷移するが、Note Offはvol依存
            shared_mem.tapping = 0x0;
            control->keyon = 0x1;
            control->interpolation = 0x1;
            control->block = p.block;
            control->fnum = p.fnum;
            control->vovol = vol;
        }

        /***** IMUの結果でコマンド調整 *****/
        // TODO: here
    } else {
        // Note Off
        control->keyon = 0x0;
        shared_mem.has_keyon = 0x0;
    }

    /***** 結果を反映 *****/
    queue_enqueue_ptr();
}

#include "sound.h"

// マルチスレッドにするならQueueに積む際にDCacheFlushしよう
static sound_command_t* control;

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

    // control allocate
    control = alloc_sound_control();
}
void sound_update() {
    /***** ADC入力値アベレージング (range外でもやっておかないと値が突然飛ぶ) *****/
    // ADCの値は何もしてなければ最大値で反転しているので注意
    uint32_t slider    = average(shared_mem.adc_slider     , &slider_average);
    uint32_t pressure0 = average(shared_mem.adc_pressure[0], &pressure_average[0]);
    uint32_t pressure1 = average(shared_mem.adc_pressure[1], &pressure_average[1]);
    uint32_t pressure2 = average(shared_mem.adc_pressure[2], &pressure_average[2]);
    // 遅いけど音階選択
    float ratio = (slider - shared_mem.sound_setting.slider_low_limit) / (float)(shared_mem.sound_setting.slider_high_limit - shared_mem.sound_setting.slider_low_limit);
    uint32_t pitch_index = (uint32_t)(ratio * PITCH_TABLE_N); // Accで増減するのでまだテーブルは引かない
    // 圧力選択(一番小さい値を採用)
    uint32_t pressure = ((pressure1 < pressure2) ? 
            ((pressure0 < pressure1) ? pressure0 : pressure1):
            ((pressure0 < pressure2) ? pressure0 : pressure2)
        ); // は、何この可読性の低いゴミコード
    // ADC12bit(inverted) -> 音量4bit 適当に丸める
    uint8_t vol = ((~(pressure >> 8)) & 0x0f);

    // 下方向を向いていたら(+現在トリガを引いていなければ) タッピングモードに切り替える
    uint8_t is_tapping = ((vol == 0) && shared_mem.acc[1] > shared_mem.sound_setting.acc_tapping_mode_y) ? 1 : 0;
    uint8_t slider_valid =  ((slider > shared_mem.sound_setting.slider_low_limit) &&
                             (slider < shared_mem.sound_setting.slider_high_limit));
    uint8_t vol_valid = vol > 0;
    /***** Commanbd生成 *****/
    if (is_tapping) {
        // TODO: sliderの触った場所で即時音を出す。音量はvol依存。Note OffはSlider依存
    } else {
        // TODO: volの値に応じて音を出す。sliderの位置で音階は遷移するが、Note Offはvol依存
    }

    /***** IMUの結果でコマンド調整 *****/
    // TODO: here

    /***** 結果を反映 *****/
    // TODO: here

}

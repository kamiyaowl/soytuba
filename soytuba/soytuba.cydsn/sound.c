#include "sound.h"

// マルチスレッドにするならQueueに積む際にDCacheFlushしよう
volatile average_t slider_average = {};
volatile average_t pressure_average[SHARED_MEM_PRESSURE_N] = {};
volatile int32_t pitch_shift_status = 0; // 現在のピッチシフト数

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
    shared_mem.sound_setting.tapping_vovol = 0x54;
    shared_mem.sound_setting.gyro_x_shift = 9;
    shared_mem.sound_setting.gyro_y_shift = 9;
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
        uint8_t has_trigger = (!shared_mem.has_keyon); // 以前音は出ていない
        shared_mem.has_keyon = 0x1;

        // 遅いけど音階選択
        float ratio = (slider - shared_mem.sound_setting.slider_low_limit) / (float)(shared_mem.sound_setting.slider_high_limit - shared_mem.sound_setting.slider_low_limit);
        uint32_t pitch_index = (uint32_t)(ratio * PITCH_TABLE_SLIDER_RANGE + PITCH_TABLE_SLIDER_MIN); // Accで増減するのでまだテーブルは引かない

        // IMU Table shift
        // 上下に振ったときにピッチシフトさせる。Gyroは32.8LSB/(deg/sec)なのでで約1revolution/secぐらい
        if(has_trigger) {
            pitch_shift_status = 0x0;
        } else {
            uint8_t gyro_negative = shared_mem.gyro[1] < 0;
            uint32_t gyro_abs = gyro_negative ? (-shared_mem.gyro[1]) : shared_mem.gyro[1];
            uint32_t shift = (gyro_abs >> shared_mem.sound_setting.gyro_y_shift);
            if (gyro_negative) {
                pitch_shift_status -= shift;
            } else {
                pitch_shift_status += shift;
            }
        }

        // IMU Vibrato
        // TODO

        // 一応境界チェックもしておく
        int32_t index = pitch_index + pitch_shift_status;
        if (index < 0) index = 0;
        if (index >= PITCH_TABLE_N) index = PITCH_TABLE_N - 1; // Sliderよりも広い範囲の音が出せるようにしておく
        pitch_t p = PITCH_TABLE[index];

        // タッピングの有無で音の鳴らし方を変える
        if (is_tapping) {
            shared_mem.tapping = 0x1;
            // sliderの触った場所で即時音を出す。音量はvol依存。Note OffはSlider依存
            control->keyon = 0x1;
            control->interpolation = 0x0; // 連続しない
            control->block = p.block;
            control->fnum = p.fnum;
            control->vovol = shared_mem.sound_setting.tapping_vovol; // volによらずに適当に出す
        } else {
            // volの値に応じて音を出す。sliderの位置で音階は遷移するが、Note Offはvol依存
            shared_mem.tapping = 0x0;
            control->keyon = 0x1;
            control->interpolation = 0x1; // 音の補完もついてる
            control->block = p.block;
            control->fnum = p.fnum;
            control->vovol = vol; // pressure押す力が弱ければ音が消える
        }
    } else {
        // Note Off
        control->keyon = 0x0;
        shared_mem.has_keyon = 0x0;
    }

    /***** 結果を反映 *****/
    queue_enqueue_ptr();
}

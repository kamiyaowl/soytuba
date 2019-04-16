#ifndef SOUND_H
#define SOUND_H

#include "shared_mem.h"
#include "queue.h"
#include <stdint.h>

// slider, pressureの入力値アベレージング最大値
#define SOUND_AVERAGE_MAX (8)

typedef struct tag_pitch_t {
    uint8_t block;
    uint16_t fnum;
} pitch_t;

// 多少無駄があるけどPROGMEM余っているので今はインデクシング速度優先。だめなら計算する
// TODO: 使ってみた感じで範囲は決める
#define PITCH_TABLE_N (36)
static const pitch_t PITCH_TABLE[PITCH_TABLE_N] = {
    {3, 	357},   // C2   130.8
    {3, 	378},   // C#2  138.6
    {3, 	401},   // D2   146.8
    {3, 	425},   // D#2  155.6
    {3, 	450},   // E2   164.8
    {3, 	477},   // F2   174.6
    {3,     505},   // F#2  185
    {3,     535},   // G2   196
    {3, 	567},   // G#2	207.7
    {3,     601},   // A2	220	3
    {3, 	637},   // A#2	233.1
    {3, 	674},   // B2	246.9
    {4, 	357},   // C3	261.6
    {4, 	378},   // C#3	277.2
    {4, 	401},   // D3	293.7
    {4, 	425},   // D#3	311.1
    {4, 	450},   // E3	329.6
    {4, 	477},   // F3	349.2
    {4,     505},   // F#3	370	4
    {4,     535},   // G3	392	4
    {4, 	567},   // G#3	415.3
    {4,     601},   // A3	440	4
    {4, 	637},   // A#3	466.2
    {4, 	674},   // B3	493.9
    {5, 	357},
    {5, 	378},
    {5, 	401},
    {5, 	425},
    {5, 	450},
    {5, 	477},
    {5,     505},
    {5,     535},
    {5, 	567},
    {5,     601},
    {5, 	637},
    {5, 	674},
};
void sound_init();
void sound_update();

#endif

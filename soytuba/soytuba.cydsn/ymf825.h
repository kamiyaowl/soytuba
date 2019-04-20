#ifndef YMF825_H
#define YMF825_H

#include "project.h"
#include "queue.h"

/////////////////////////////////////////////////////////////////////////////
// SPI porting
inline void ymf825_spi_cs(uint8_t assert) {
    REG_SS_YM825_Write(assert ? 0x0 : 0x1);
}
inline void ymf825_spi_transfer(const uint8_t* src, uint8_t length) {
    ymf825_spi_cs(0x1);
    SPIM_YMF825_PutArray(src, length);
    while(!(SPIM_YMF825_ReadStatus() & SPIM_YMF825_STS_SPI_DONE)) {}
    ymf825_spi_cs(0x0);
}
inline void ymf825_spi_write_reg(uint8_t addr, uint8_t data) {
    uint8_t datas[] = {addr, data};
    ymf825_spi_transfer(datas, 2);
}
inline void ymf825_delay(uint32_t ms){
    CyDelay(ms);
}
inline void ymf825_spi_init() {
    ymf825_spi_cs(0x0);
    SPIM_YMF825_Start();
}

/////////////////////////////////////////////////////////////////////////////
// Application
// from https://github.com/yamaha-webmusic/ymf825board/blob/master/sample1/ymf825board_sample1/ymf825board_sample1.ino

void ymf825_set_tone(void);
void ymf825_set_ch(void);

void ymf825_init();
void ymf825_update(uint8_t flush_all);

#endif

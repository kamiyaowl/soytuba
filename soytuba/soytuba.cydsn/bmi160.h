#include "project.h"
#include "shared_mem.h"

#ifndef BMI160_H
#define BMI160_H


/////////////////////////////////////////////////////////////////////////////
// SPI porting
inline void bmi160_spi_cs(uint8_t assert) {
    REG_SS_YM825_Write(assert ? 0x0 : 0x1);
}
inline void bmi160_delay(uint32_t ms){
    CyDelay(ms);
}
inline void bmi160_spi_wait_done(){
    uint8_t data;
    do{
        data = SPIM_BMI160_ReadTxStatus();
    } while(!(data & SPIM_BMI160_STS_SPI_DONE));
}
inline void bmi160_spi_transfer(const uint8_t* tx_data, uint8_t* rx_data, uint8_t length) {
    SPIM_BMI160_ClearFIFO();
    
    bmi160_spi_cs(0x1);
    for(uint32_t i = 0 ; i < length ; ++i) {
        SPIM_BMI160_WriteTxData(tx_data[i]);
        uint8_t rx = SPIM_BMI160_ReadRxData();
        if (rx_data != NULL) {
            rx_data[i] = rx;
        }
        bmi160_spi_wait_done();
    }
    bmi160_spi_cs(0x0);
}
inline void bmi160_spi_write_reg(uint8_t addr, uint8_t data) {
    uint8_t datas[] = {addr, data};
    bmi160_spi_transfer(datas, NULL, 2);
}
inline void bmi160_spi_init() {
    bmi160_spi_cs(0x0);
    SPIM_BMI160_Start();
}

/////////////////////////////////////////////////////////////////////////////
// Application
// https://www.mouser.com/ds/2/783/BST-BMI160-DS000-07-786474.pdf

void bmi160_init();
void bmi160_update();

#endif

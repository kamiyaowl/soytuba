#include "bmi160.h"

void bmi160_init(){
    bmi160_spi_init();
    // cmd softreset
    bmi160_spi_write_reg(0x7e, 0xb6);
    bmi160_delay(10);
    
    // cmd set pmu of acc
    bmi160_spi_write_reg(0x7e, 0x11);
    bmi160_delay(10);

    // cmd set pmu of gyro
    bmi160_spi_write_reg(0x7e, 0x15);
    bmi160_delay(10);
    
    // acc range
    bmi160_spi_write_reg(0x041, 0x08); // 3:2g, 5:4g, 8: 8g, 12:16g 
    // gyro range
    bmi160_spi_write_reg(0x43, 0x01); // 001: 1000deg/sec
}

void bmi160_update() {
    uint8_t write_buf[2] = { 0x00 | 0x80 }; // 0x0c: GYR_X[7:0], 0x0d: GYRO_X[15:8]...
    uint8_t read_buf[2] = {}; // 先頭はダミーが入る

    bmi160_spi_transfer(write_buf, read_buf, 2);
    shared_mem.gyro[0] = read_buf[1];
//    // read cmdは最初のアドレスバイトの先頭を立てる
//    uint8_t write_buf[13] = { 0x0c | 0x80 }; // 0x0c: GYR_X[7:0], 0x0d: GYRO_X[15:8]...
//    uint8_t read_buf[13] = {}; // 先頭はダミーが入る
//    
//    bmi160_spi_transfer(write_buf, read_buf, 13);
//    
//    shared_mem.gyro[0] = (read_buf[1] & 0xff) | ((uint16_t)read_buf[2] << 8);
//    shared_mem.gyro[1] = (read_buf[3] & 0xff) | ((uint16_t)read_buf[4] << 8);
//    shared_mem.gyro[2] = (read_buf[5] & 0xff) | ((uint16_t)read_buf[6] << 8);
//    
//    shared_mem.acc[0] = (read_buf[7]  & 0xff) | ((uint16_t)read_buf[8]  << 8);
//    shared_mem.acc[1] = (read_buf[9]  & 0xff) | ((uint16_t)read_buf[10] << 8);
//    shared_mem.acc[2] = (read_buf[11] & 0xff) | ((uint16_t)read_buf[12] << 8);
}
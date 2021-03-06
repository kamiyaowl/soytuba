#include "bmi160.h"

void bmi160_init(){
    bmi160_spi_init();
    // cmd softreset
    bmi160_spi_write_reg(0x7e, 0xb6);
    bmi160_delay(100);
    
    // cmd set pmu of acc
    bmi160_spi_write_reg(0x7e, 0x11);
    bmi160_delay(100);

    // cmd set pmu of gyro
    bmi160_spi_write_reg(0x7e, 0x15);
    bmi160_delay(100);
    
    // acc range
    bmi160_spi_write_reg(0x041, 0x08); // 3:2g(16384LSB/g), 5:4g(8192LSB/g), 8: 8g(4096LSB/g), 12:16g(2048LSB/g)
    // gyro range
    bmi160_spi_write_reg(0x43, 0x01); // 001: 1000deg/sec(32.8LSB/(deg/sec))
}

void bmi160_update() {
    // read cmdは最初のアドレスバイトの先頭を立てる
    uint8_t write_buf[13] = { 0x0c | 0x80 }; // 0x0c: GYR_X[7:0], 0x0d: GYRO_X[15:8]...
    uint8_t read_buf[13] = {}; // 先頭はダミーが入る
    
    bmi160_spi_transfer(write_buf, read_buf, 13);
    
    // 軸反転対応もここで得やる
    int16_t raw_gyro_x = (read_buf[1] & 0xff) | ((uint16_t)read_buf[2] << 8);
    int16_t raw_gyro_y = (read_buf[3] & 0xff) | ((uint16_t)read_buf[4] << 8);
    int16_t raw_gyro_z = (read_buf[5] & 0xff) | ((uint16_t)read_buf[6] << 8);
    shared_mem.gyro[0] = -raw_gyro_y; // 右に傾けると+
    shared_mem.gyro[1] = -raw_gyro_x; // 前に傾けると+
    shared_mem.gyro[2] = raw_gyro_z; // 時計回りで+
    
    int16_t raw_acc_x = (read_buf[7]  & 0xff) | ((uint16_t)read_buf[8]  << 8);
    int16_t raw_acc_y = (read_buf[9]  & 0xff) | ((uint16_t)read_buf[10] << 8);
    int16_t raw_acc_z = (read_buf[11] & 0xff) | ((uint16_t)read_buf[12] << 8);
    shared_mem.acc[0] = -raw_acc_x;// 右に傾けると+
    shared_mem.acc[1] = raw_acc_y; // 前に傾けると+
    shared_mem.acc[2] = -raw_acc_z; // 何もしなくても+1G
}
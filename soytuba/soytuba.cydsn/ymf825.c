#include "ymf825.h"

void ymf825_init(void) {
    ymf825_spi_init();
    
   ymf825_spi_write_reg( 0x1D, 0x0 ); // 5V
   ymf825_spi_write_reg( 0x02, 0x0E );
   ymf825_delay(1);
   ymf825_spi_write_reg( 0x00, 0x01 );//CLKEN
   ymf825_spi_write_reg( 0x01, 0x00 ); //AKRST
   ymf825_spi_write_reg( 0x1A, 0xA3 );
   ymf825_delay(1);
   ymf825_spi_write_reg( 0x1A, 0x00 );
   ymf825_delay(30);
   ymf825_spi_write_reg( 0x02, 0x04 );//AP1,AP3
   ymf825_delay(1);
   ymf825_spi_write_reg( 0x02, 0x00 );
   //add
   ymf825_spi_write_reg( 0x19, 0xF0 );//MASTER VOL
   ymf825_spi_write_reg( 0x1B, 0x3F );//interpolation
   ymf825_spi_write_reg( 0x14, 0x00 );//interpolation
   ymf825_spi_write_reg( 0x03, 0x01 );//Analog Gain
   
   ymf825_spi_write_reg( 0x08, 0xF6 );
   ymf825_delay(21);
   ymf825_spi_write_reg( 0x08, 0x00 );
   ymf825_spi_write_reg( 0x09, 0xF8 );
   ymf825_spi_write_reg( 0x0A, 0x00 );
   
   ymf825_spi_write_reg( 0x17, 0x40 );//MS_S
   ymf825_spi_write_reg( 0x18, 0x00 );
}

void ymf825_set_tone(void){
    // https://kanpapa.com/today/2017/08/ymf825-fm-board.html
    unsigned char tone_data[36] ={
        // write addr
        0x07,
        // tone data
        0x81,//header
        // T_ADR 0
        // Entire Tone Setting
        0x01, // BO (Basic Octave)
        0x67, // LFO,ALG
        //Operator1 Setting 
        0x00, // SR, XOF, KSR
        0xE9, // RR, DR
        0x91, // AR, SL
        0x9D, // TL, KSL
        0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
        0x10, // MULTI(magnification of frequency), DT(detune)
        0x40, // WS(wave shape), FB(FM feedback level)
        // Operator2 Setting
        0x20, // SR, XOF, KSR
        0x3b, // RR, DR
        0x91, // AR, SL
        0x73, // TL, KSL
        0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
        0x50, // MULTI(magnification of frequency), DT(detune)
        0x40, // WS(wave shape), FB(FM feedback level)
        // Operator3 Setting
        0x10, // SR, XOF, KSR
        0x4b, // RR, DR
        0xa1, // AR, SL
        0x5B, // TL, KSL
        0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
        0x10, // MULTI(magnification of frequency), DT(detune)
        0x41, // WS(wave shape), FB(FM feedback level)
        // Operator4 Setting
        0x20, // SR, XOF, KSR
        0x6b, // RR, DR
        0xb1, // AR, SL
        0x02, // TL, KSL
        0x01, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
        0x10, // MULTI(magnification of frequency), DT(detune)
        0x80, // WS(wave shape), FB(FM feedback level)
        0x80,0x03,0x81,0x80, // End(80H,03H,81H,80H)
    };
  
   ymf825_spi_write_reg( 0x08, 0xF6 );
   ymf825_delay(1);
   ymf825_spi_write_reg( 0x08, 0x00 );
  
   ymf825_spi_transfer(&tone_data[0], 36);//write to FIFO
}

void ymf825_set_ch(void){
   ymf825_spi_write_reg( 0x0F, 0x30 );// keyon = 0
   ymf825_spi_write_reg( 0x10, 0x71 );// chvol
   ymf825_spi_write_reg( 0x11, 0x00 );// XVB
   ymf825_spi_write_reg( 0x12, 0x08 );// FRAC
   ymf825_spi_write_reg( 0x13, 0x00 );// FRAC  
}

void ymf825_keyon(uint8_t fnumh, uint8_t fnuml){
   ymf825_spi_write_reg( 0x0B, 0x00 );//voice num
   ymf825_spi_write_reg( 0x0C, 0x54 );//vovol
   ymf825_spi_write_reg( 0x0D, fnumh );//fnum
   ymf825_spi_write_reg( 0x0E, fnuml );//fnum
   ymf825_spi_write_reg( 0x0F, 0x40 );//keyon = 1  
}
void ymf825_keyon2(uint16_t fnum){
    ymf825_keyon((fnum >> 8) & 0xff, fnum & 0xff);
}


void ymf825_keyoff(void){
   ymf825_spi_write_reg( 0x0F, 0x00 );//keyon = 0
}


void ymf825_update() {
    // TODO: sound_updateがshared_memに書いた値を使って音を鳴らす
    // TEST
  ymf825_keyon(0x14,0x65);
  ymf825_delay(100);
  ymf825_keyoff();
  ymf825_delay(100);
  ymf825_keyon(0x1c,0x11);
  ymf825_delay(100);
  ymf825_keyoff();
  ymf825_delay(100);
  ymf825_keyon(0x1c,0x42);
  ymf825_delay(100);
  ymf825_keyoff();
  ymf825_delay(100);
  ymf825_keyon(0x1c,0x5d);
  ymf825_delay(100);
  ymf825_keyoff();
  ymf825_delay(100);
  ymf825_keyon(0x24,0x17);
  ymf825_delay(100);
  ymf825_keyoff();
  ymf825_delay(100);
  ymf825_keyon(0x24,0x17);
  ymf825_delay(500);
  ymf825_keyon(0x14,0x65);
  ymf825_delay(500);
  ymf825_keyoff();
  ymf825_delay(100);
}
#include "shared_mem.h"
/////////////////////////////////////////////////////////////
// init DMA
/* Defines for DMA_SLIDER */
#define DMA_SLIDER_BYTES_PER_BURST 2
#define DMA_SLIDER_REQUEST_PER_BURST 1
#define DMA_SLIDER_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_SLIDER_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_SLIDER */
/* Move these variable declarations to the top of the function */
uint8 DMA_SLIDER_Chan;
uint8 DMA_SLIDER_TD[1];

/* Defines for DMA_PRESSURE */
#define DMA_PRESSURE_BYTES_PER_BURST 2
#define DMA_PRESSURE_REQUEST_PER_BURST 1
#define DMA_PRESSURE_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_PRESSURE_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_PRESSURE */
/* Move these variable declarations to the top of the function */
uint8 DMA_PRESSURE_Chan;
uint8 DMA_PRESSURE_TD[1];

void shared_mem_dma_init() {

    /* DMA Configuration for DMA_SLIDER */
    DMA_SLIDER_Chan = DMA_SLIDER_DmaInitialize(DMA_SLIDER_BYTES_PER_BURST, DMA_SLIDER_REQUEST_PER_BURST, 
        HI16(DMA_SLIDER_SRC_BASE), HI16(DMA_SLIDER_DST_BASE));
    DMA_SLIDER_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_SLIDER_TD[0], 1, CY_DMA_DISABLE_TD, CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_SLIDER_TD[0], LO16((uint32)ADC_SLIDER_DEC_SAMP_PTR), LO16((uint32)shared_mem.adc_slider));
    CyDmaChSetInitialTd(DMA_SLIDER_Chan, DMA_SLIDER_TD[0]);
    CyDmaChEnable(DMA_SLIDER_Chan, 1);

    /* DMA Configuration for DMA_PRESSURE */
    DMA_PRESSURE_Chan = DMA_PRESSURE_DmaInitialize(DMA_PRESSURE_BYTES_PER_BURST, DMA_PRESSURE_REQUEST_PER_BURST, 
        HI16(DMA_PRESSURE_SRC_BASE), HI16(DMA_PRESSURE_DST_BASE));
    DMA_PRESSURE_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_PRESSURE_TD[0], 3, CY_DMA_DISABLE_TD, CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_PRESSURE_TD[0], LO16((uint32)ADC_SAR_PRESSURE_SAR_SAR_WRK0_PTR), LO16((uint32)shared_mem.adc_pressure[0]));
    CyDmaChSetInitialTd(DMA_PRESSURE_Chan, DMA_PRESSURE_TD[0]);
    CyDmaChEnable(DMA_PRESSURE_Chan, 1);
}

/////////////////////////////////////////////////////////////
// init

void shared_mem_init() {
    shared_mem.adc_slider = 0;
    for(uint8_t i = 0 ; i < SHARED_MEM_PRESSURE_N ; ++i) {
        shared_mem.adc_pressure[i] = 0;
    }
    
    shared_mem_dma_init();
}

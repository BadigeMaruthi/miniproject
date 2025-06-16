//adc_defines.h
//clock defines
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define  ADC_CLK  3000000
#define CLKDIV ((CCLK/ADC_CLK)-1)
//ADCR sfr defines
#define CLKDIV_BITS      8
#define PDN_BIT         21
#define ADC_START_CONB  24
//ADDR sfr defines
#define ADCDVAL_BITS 6
#define DONE_BIT     31

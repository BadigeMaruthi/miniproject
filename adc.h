//adc.h
#include"types.h"
void Init_ADC(void);
//f32 readadc(u38 chno);
void Read_ADC(u8 chno,u32 *adcval,f32*eVR);


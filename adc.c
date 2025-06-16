//adc.c
#include<lpc21xx.h>
#include"types.h"
#include"delay.h"

#include"pin_connect_block_defines.h"
#include"adc_defines.h"
void Init_ADC(void)
{
	   //cfg p0.27 to p0.30 analog inputs
	  CfgPortPinFunc(0,27,1);
	 //CfgPortPinFunc(0,28,1);
	//cfgportpinfun(0,29,1);
 //cfgportpinfun(0,30,1);
	ADCR=(1<<PDN_BIT)|((CLKDIV<<CLKDIV_BITS));
}
void Read_ADC(u8 chno,u32* adcDval,f32* eVR)
{
	ADCR&=0xffffff00;  // clear adc presious channales
	ADCR|=1<<chno;     // set adc new channel
	ADCR|=1<<ADC_START_CONB; //intial samplaming &convertion
	delay_US(3);
	while(((ADDR>>DONE_BIT)&1)==0);
		ADCR&=~(1<<ADC_START_CONB);//read /extract 10_bit digit data
		*adcDval=(ADDR>>ADCDVAL_BITS)&1023;
		//convert to equlinet
		*eVR=(3.3/1023)*(*adcDval);
		//return eVR;
}

// main.c
#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "types.h"
#include "delay.h"
#include "rtc.h"
#include "settings_vailds.h"
#include "adc_defines.h"
#include "adc.h"
#include "uart.h"
#include "uart_defines.h"
#include "pin_connect_block_defines.h"
#define PIN_FUN2 1
#define EINT0_INPUT_PIN PIN_FUN2
#define EINT0_PIN  16// P0.16
#define EINT0_VIC_CHNO 14
#define LED  30       //0.28 for interrput status
#define UPDATE_LCD 3
#define UPDATE_UART 5
extern s32 hour,min,sec,date,month,year,day;
void  eint0_isr(void)__irq;
u32 inp_flag=0;
u32 PSW=1234,temp_sp=32,temp;
static s32 uart_last_min = -1;
// Main function
int main()
{        
	       f32 eVR;
	       u32 adcval;
	      // Initialize the LCD
         InitLCD();
        // Initialize RTC
         RTC_Init();
        //Initialize KPM
         Initkpm();
	      //Initialize ADC
	        Init_ADC();
	        Init_UART0();
	        IODIR1|=1<<LED;
				    CfgPortPinFunc(0,16,EINT0_INPUT_PIN);
			     //cfg vic for EINT0 as irq types
	        //VICIntSelect=0;//def all interrpts are irq
	       //cfgVIC for Enable EINT0 interrput
	       VICIntEnable=1<<EINT0_VIC_CHNO;
	      //cfg ENT0 as V1 IRQ highest peroprity(0)
	       VICVectCntl0= (1 << 5)|EINT0_VIC_CHNO;
	      //load ENTN0.isr address info v.irq reg
      	VICVectAddr0 = (u32)eint0_isr;             // ISR address
       // Enable EINT0
        EXTMODE = (1 << 0);    // Edge trigring
        EXTPOLAR = 0;				// Falling edge triggered
	 while (1)
        {
								
                GetRTCTimeInfo(&hour,&min,&sec);
                DisplayRTCTime(hour,min,sec);
                GetRTCDateInfo(&date,&month,&year);
                DisplayRTCDate(date,month,year);
                GetRTCDay(&day);
                DisplayRTCDay(day);
					      Read_ADC(0,&adcval,&eVR);
		            cmdLCD(GOTO_LINE2_POS0+10);
					      temp=(eVR*100);
		            u32LCD(temp);
	        	    strLCD("degC");
					      delay_S(3);
					      if(temp>=temp_sp)
								{
									//IOPIN1^=1<<LED;
									IOSET1|=1<<LED;
									delay_S(1);
								  cmdLCD(CLEAR_LCD);
									strLCD("OVER-TEMP ALERT");
		              cmdLCD(GOTO_LINE2_POS0);
									strLCD("EXCCEDS SET PNT");
									delay_S(5);
									cmdLCD(CLEAR_LCD);
									U0_TxStr("[ALERT] Temp:");
			            upadte_to_uart(hour,min,sec,date,month,year,day,temp);
									U0_TxStr(" - OVER TEMP!");
									IOCLR1|=1<<LED; 
								}
             if ((min % UPDATE_UART == 0) && (min != uart_last_min)) 
							 {
                      uart_last_min = min;
                    U0_TxStr("[INFO] Temp:");
							 upadte_to_uart(hour, min, sec, date, month, year, day, temp);
							 }
                if(inp_flag)
								{
									 U0_TxStr("*** Time Editing Mode Activated ***");
									 EDIT_FUN();
									 inp_flag=0;
									 cmdLCD(CLEAR_LCD);
								}					
								
							}				
}
void eint0_isr()__irq
{
	inp_flag=1;
	//clear EINT0 status flag in ext int peripherial
	EXTINT=1<<0;
	//clear EINT0_status in VIC peripheral
	VICVectAddr=0;
}

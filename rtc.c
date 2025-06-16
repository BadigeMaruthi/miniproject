//rtc.c
#include<lpc21xx.h>

#include"types.h"
#include"rtc_defines.h"
#include"lcd_defines.h"
#include"lcd.h"
void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);
void SetRTCDay(u32 day);

 char week [][4]=
 {
	 "SUN","MON","TUE","WED","THU","FRI","SAT"
 };
 
 //RTC Initialization:configures and enables the RTC
 
 void RTC_Init(void)
 {
	 //Disable &reset the RTC
	 CCR=RTC_RESET;
	 
   // set prescaler integer part
	 PREINT = PREINT_VAL;
	 
	 // set prescaler fractional part
	 PREFRAC = PREFRAC_VAL;
	 
	 //enalble the RTC
	 CCR = RTC_ENABLE;
   SetRTCTimeInfo(23,20,0);      
   SetRTCDateInfo(15,6,25);   
   SetRTCDay(0);                  
	 
 }
void GetRTCTimeInfo(s32 *hr,s32 *mi,s32 *se)
{
   *hr=HOUR;
   *mi=MIN;
	 *se=SEC;
}
void GetRTCDateInfo(s32 *date, s32 *month,s32 *year)
{
	 *date=DOM;
	 *month=MONTH;
   *year=YEAR;
}
void DisplayRTCTime(u32 hr,u32 mi,u32 se)
{
	cmdLCD(GOTO_LINE1_POS0);
	charLCD((hr/10)+48);
	charLCD((hr%10)+48);
	charLCD(':');
	charLCD((mi/10)+48);
	charLCD((mi%10)+48);
	charLCD(':');
	charLCD((se/10)+48);
	charLCD((se%10)+48);
}
void DisplayRTCDate(u32 dt,u32 mo,u32 yr)
{
	cmdLCD(GOTO_LINE2_POS0);
	charLCD((dt/10)+48);
	charLCD((dt%10)+48);
	charLCD('/');
	charLCD((mo/10)+48);
	charLCD((mo%10)+48);
	charLCD('/');
	u32LCD(yr);
}
void GetRTCDay(s32 *d)
{
	*d=DOW;
}
void DisplayRTCDay(u32 d)
{
	cmdLCD(GOTO_LINE1_POS0+10);
	strLCD(week[d]);
}
void SetRTCTimeInfo(u32 hour,u32 min,u32 sec)
{
	//set hours
	HOUR = hour;
	// set min
	MIN=min;
	// set seconds
	SEC =sec;
}
void SetRTCDateInfo(u32 dt,u32 mo,u32 yr)
{
	//set date
	DOM = dt;
	//set month
	MONTH = mo;
	// set year
	YEAR = yr;
}
void SetRTCDay(u32 day)
{
	DOW = day;
}


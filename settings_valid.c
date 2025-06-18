//settings_valid.c
#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "settings_vailds.h"
#include "kpm.h"
#include "types.h"
#include "delay.h"
#include "rtc.h"
extern char week[][4];
extern u32 inp_flag, PSW,temp_sp;
s32 hour, min, sec, date, month, year, day;
void EDIT_FUN()
{
	 u32 key;
    u8 ch,n=3;
    cmdLCD(CLEAR_LCD);
    strLCD(" EDITING  ");
		cmdLCD(GOTO_LINE2_POS0);
    strLCD("         MODE");
    delay_S(4);
	L1:cmdLCD(CLEAR_LCD);
    strLCD("ENTER PIN");
    cmdLCD(GOTO_LINE2_POS0);
    key = PIN();
    u32LCD(key);
    if (key == PSW)
    { 
        cmdLCD(CLEAR_LCD);
        strLCD("1.TIME & DATE");
        cmdLCD(GOTO_LINE2_POS0);
        strLCD("2.TEMP SET POINT ");
			  delay_S(4);
			  cmdLCD(CLEAR_LCD);
        strLCD("3.PIN CHANGE");
        delay_S(4);

    L2:
        cmdLCD(CLEAR_LCD);
        strLCD("ENTER CHOICE");
        cmdLCD(GOTO_LINE2_POS0);
         ch = readnum();
         ch = ch + '0'; 
        switch (ch)
        {
            case '1': EDIT_TIME(); break;
            case '2': EDIT_TEMP_SET_PNT(); break;
					  case '3': PIN_CHAMGE();break;
            default:
							   cmdLCD(CLEAR_LCD);
                strLCD("ENTER VALID");
                delay_S(5);
                goto L2;
        }
			}

else 
	{
        n--;
        cmdLCD(CLEAR_LCD);
        strLCD("INVALID PIN");
        cmdLCD(GOTO_LINE2_POS0);
        if (n > 0) 
					{
            strLCD("TRIES LEFT: ");
            u32LCD(n);
            delay_S(3);
            goto L1;
        } 
					else 
						{
            cmdLCD(CLEAR_LCD);
            strLCD("NO MORE TRIES");
            cmdLCD(GOTO_LINE2_POS0);
            strLCD("TRY LATER");
            delay_S(4);
        }
    }
}
void EDIT_TIME()
{
    u8 ch;

M:
    cmdLCD(CLEAR_LCD);
    strLCD("1.H 2.M 3.S 4.D");
    cmdLCD(GOTO_LINE2_POS0);
    strLCD("5.M 6.Y 7.D 8.E");
    delay_S(5);

     cmdLCD(CLEAR_LCD);
     strLCD("ENTER THE CHOICE");
     ch = readnum();
	   ch = ch + '0';

    switch (ch)
    {
        case '1': HOUR  = SET_HOUR(); break;
        case '2': MIN   = SET_MIN(); break;
        case '3': SEC   = SET_SEC(); break;
        case '4': date  = SET_DATE(); break;
        case '5': month = SET_MONTH(); break;
        case '6': year  = SET_YEAR(); break;
        case '7': DOW   = SET_DAY(); break;
        case '8': return;
        default:
            cmdLCD(CLEAR_LCD);
            strLCD("ENTER VALID");
            delay_MS(5);
            goto M;
    }
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if(date>=30&&month==2)
			{
				cmdLCD(CLEAR_LCD);
				strLCD("SET VAILD DATE");
				delay_S(4);
				goto M;
				
			}
		}
		else
		{
			  DOM   = date;
        MONTH = month;
        YEAR  = year;
		}
			
				
}
void EDIT_TEMP_SET_PNT()
{
    u32 temp;

A:
    cmdLCD(CLEAR_LCD);
    strLCD("ENTER SET POINT");
    cmdLCD(GOTO_LINE2_POS0);
    temp = readnum();

    if (temp < 10 || temp > 90)
    {
        cmdLCD(CLEAR_LCD);
        strLCD("SET IN RANGE ");
        cmdLCD(GOTO_LINE2_POS0);
        strLCD("10-90");
        delay_MS(4);
        goto A;
    }
    temp_sp = temp;
}
void PIN_CHAMGE()
{
	   u32 temp;
    cmdLCD(CLEAR_LCD);
    strLCD("ENTER PIN");
    cmdLCD(GOTO_LINE2_POS0);
    temp = readnum();
	  if(temp==PSW)
		{
		   cmdLCD(CLEAR_LCD);
       strLCD("ENTER NEW PIN 4DG");
       cmdLCD(GOTO_LINE2_POS0);
       PSW = readnum();
       delay_S(4);
			 strLCD("SUSCCSS");
			 delay_S(4);
		}
	}

	
	
s8  SET_HOUR()
{
	s8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER HOUR(0-23)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t>23)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD HOUR");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER HOUR(0-23)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}



s8  SET_MIN()
{
	s8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER MINS(0-59)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t>59)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD MINS");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER MINS(0-59)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}



u8  SET_SEC()
{
	u8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER SECS(0-59)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t==0||t>59)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD SECS");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER SECS(0-59)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}



u8  SET_DATE()
{
	u8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER DATE(0-31)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t==0||t>31)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD DATE");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER SECS(1-31)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}

u8  SET_MONTH()
{
u8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER MONTH(1-12)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t==0||t>12)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD MONTH");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER MONTH(1-12)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}



u8  SET_DAY()
{
  u8 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER DAY(0-6)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t>6)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD DAY");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER DAY(0-6)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}


u16 SET_YEAR()
{
  u16 t;
t1:cmdLCD(CLEAR_LCD);
	strLCD("ENTER (0-4098)");
	cmdLCD(GOTO_LINE2_POS0);
	t=readnum();
	if(t==0||t>4098)
	{
		cmdLCD(CLEAR_LCD);
  	strLCD("INVAILD YEAR");
	  cmdLCD(GOTO_LINE2_POS0);
		strLCD("ENTER (0-4098)");
		delay_S(4);
		goto t1;
	}
	else
		return t;
}

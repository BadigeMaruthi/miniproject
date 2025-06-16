//kpm.c
#include"types.h"
#include"delay.h"
#include<lpc21xx.h>
#include"lcd_defines.h"
#include"lcd.h"
#include"kpm_defines.h"
const u32 kpmLUT[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','x'},
	{'1','2','3','-'},
	{'*','0','=',' '}
};
void Initkpm(void)
{
	//cfg row line as gpio out pin
	IODIR1=15<<ROW0;
	//default all lines are any way high
}
u32 colscan(void)
{
	u32 t;
	t=((IOPIN1>>COL0)&15)<15?0:1;
	return t;
}
u32 Rowscheck(void)
{
	u32 rno;
	for(rno=0;rno<=3;rno++)
	{
		//ground every row at a time staring with 0 th row
		IOPIN1=((IOPIN1&~(15<<ROW0))|((~(1<<rno))<<ROW0));
		if(colscan()==0)
			 break;
	}
	//re-intillize all rows ground 
	IOCLR1=15<<ROW0;
	return rno;
}	
u32 colcheck(void)
{
	u32 cno;
	for(cno=0;cno<=3;cno++)
	{
		if(((IOPIN1>>(COL0+cno))&1)==0)
			 break;
	}
	return cno;
}
u32 keyscan(void)
{
	u32 rno,cno,keyV;
	//wait for any key press
	while(colscan());
	//procced to indetify row in which key is pressed
	rno=Rowscheck();
	//procced to indetify  col in which key is pressed
	cno=colcheck();
	//extract key from the lut table
	keyV=kpmLUT[rno][cno];
	return keyV;
}
	u32 readnum(void)
{
	u32 sum=0;
	s8 key;
	while(1)
	{
		key=keyscan();
		if((key>='0')&&(key<='9'))
		{
			sum=((sum*10)+(key-48));
			cmdLCD(GOTO_LINE2_POS0);
			u32LCD(sum);
			while(colscan()==0);
		}
		else if(key=='-')
		{
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("                ");
			sum=sum/10;
			cmdLCD(GOTO_LINE2_POS0);
			u32LCD(sum);
			while(colscan()==0);
		}
		else if(key=='=')
		{
			while(colscan()==0);
			break;
		}
	}
	return sum;
}
u32 PIN(void)
{
	u32 sum = 0;
	s8 key;
	u32 count = 0;
	while (1)
	{
		key = keyscan();

		if ((key >= '0') && (key <= '9'))
		{
			sum = (sum * 10) + (key - '0');
			cmdLCD(GOTO_LINE2_POS0 + count);
			charLCD('*');
			count++;
			while (colscan() == 0);
		}
		else if (key == '-')
		{
			if (count > 0)
			{
				sum = sum / 10;
				count--;
				cmdLCD(GOTO_LINE2_POS0 + count);
				charLCD(' ');
				cmdLCD(GOTO_LINE2_POS0 + count);
			}
			while (colscan() == 0);
		}
		else if (key == '=')
		{
			while (colscan() == 0);
			break;
		}
	}

	return sum;
}


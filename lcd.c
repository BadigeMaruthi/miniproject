//lcd.c
#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
void writeLCD(u8 byte)
{
        //select write opertion D0 to D7
        IOPIN0=((IOPIN0&~(0xFF<<LCD_DATA))|(byte<<LCD_DATA));
        //applying high to low enable
        IOCLR0=1<<LCD_RW;
        IOSET0=1<<LCD_EN;
        delay_US(1);
        IOCLR0=1<<LCD_EN;
        delay_MS(2);
}
void cmdLCD(u8 cmd)
{
        // select cmd reg
        IOCLR0=1<<LCD_RS;
        //write to cmd reg
         writeLCD(cmd);
}
void charLCD(u8 ascii)
{
        //select data reg
        IOSET0=1<<LCD_RS;
        //write to addres via data reg writeLCD(ascii);
        writeLCD (ascii);

}
void InitLCD(void)  //lcd intilaztion
{
        //cfg po.8 (D0) to p0.15 (D7)  rs,rw,en
        IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
        delay_MS(15);
        cmdLCD(0x30);
        delay_MS(5);
        delay_US(100);
        cmdLCD(0x30);
        delay_US(100);
        cmdLCD(0x30);
        cmdLCD(MODE_8BIT_2LINE);
        cmdLCD(DSP_ON_CUR_OFF);
        cmdLCD(CLEAR_LCD);
        cmdLCD(SHIFT_CUR_RIGHT);
}
void strLCD(s8*s)   //for string inputs to lcd
{
        while(*s)
                 charLCD(*s++);
}
void u32LCD(u32 n)
{
        s32 i=0;
        u8 digit[10];
        if(n==0)
        {
                charLCD('0');
        }
        else
        {
                while(n>0)
                {
                        digit[i]=(n%10)+48;
                        n/=10;
                        i++;
                }
                for(--i;i>=0;i--)
                charLCD(digit[i]);
        }
}
void s32LCD(s32 n)   //for  nagative number display
{
        if(n<0)
        {
                charLCD('-');
                n=-n;
        }
        u32LCD(n);
}
void f32LCD(f32 fnum,u8 ndp)  //for flaoting number
{
        s32 i;
        u32 n;
        if(fnum<0)
        {
                charLCD('-');
                fnum=-fnum;
        }
        n=fnum;
        u32LCD(n);
        charLCD('.');
        for(i=0;i<ndp;i++)
        {
                fnum=(fnum-n)*10;
                n=fnum;
                charLCD(n+48);
        }
}

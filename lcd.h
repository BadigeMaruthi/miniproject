//lcd.h
#include "types.h"
void writeLCD(u8 byte);
void cmdLCD(u8 cmd);
void charLCD(u8 ascii);
void InitLCD(void);
void strLCD(s8*);
void u32LCD(u32);
void s32LCD(s32);
void f32LCD(f32,u8);
void BuildCGRAM(s8*,u8);



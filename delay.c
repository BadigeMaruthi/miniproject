#include "types.h"
#include "delay.h"

void delay_US(u32 dlyUS)
{
	dlyUS*=12;
	while(dlyUS--);
}
void delay_MS(u32 dlyMS)
{
	dlyMS*=12000;
	while(dlyMS--);
}
void delay_S(u32 dlyS)
{
	dlyS*=1200000;
	while(dlyS--);
}


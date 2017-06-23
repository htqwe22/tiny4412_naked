#include "console.h"
#include "util.h"
#define GPM4CON (*(volatile unsigned int *)0x110002e0)
#define GPM4DAT (*(volatile unsigned int *)0x110002e4)
// key 
#define GPX3CON (*(volatile unsigned int *)0x11000c60)
#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

void mdelay(int time);
extern show_led(int num);
extern void code_relocate(void);
extern void system_clock_init(void);
extern void debug_clk_regs(int index);

int main(void)
{
	unsigned int tmp;
	unsigned int i = 1;
	
	/*Init LED*/
    tmp = GPM4CON;  
    tmp &= ~0xffff;  
    tmp |= 0x1111;  
    GPM4CON = tmp; 
	code_relocate();
	init_console();
	
	system_clock_init();
//	init_console();
	for (;;mdelay(1000),i++) {
		show_led(i);
	//	debug("hello kevin %d\r\n", i);
	}
	return 0;
}

void mdelay(int time)
{
	int j;
	for (; time > 0; time--) {
		for (j = 0; j < 500; j++) ;
	}
}


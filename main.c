#include "console.h"
#include "util.h"
#define GPM4CON (*(volatile unsigned int *)0x110002e0)
#define GPM4DAT (*(volatile unsigned int *)0x110002e4)
// key 
#define GPX3CON (*(volatile unsigned int *)0x11000c60)
#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

void mdelay(int time);
extern show_led(int num);
extern void system_clock_init(void);
extern void debug_clk_regs(int index);
extern void code_relocate(void);
extern void init_led(void);
extern unsigned int get_start(void);
extern unsigned int get_code_size(void);

int gnum[256];
int _main(unsigned int start, unsigned int sp)
{
	unsigned int link_start;
	unsigned int i = 1;
	init_console();
	code_relocate();	
	link_start = get_start();
	debug("hello world (%X, %X, %X)\n", start, link_start, sp);
	debug("GPM4CON = %X\n", GPM4CON);

//	system_clock_init();
//	init_console();
	for (;;mdelay(1000),i++) {
		show_led(i);
		debug("hello kevin %d\r\n", i);
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


#include "console.h"
#include "util.h"
#include "util_string.h"

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
extern unsigned int current_pc(void);
extern void init_ddr(void);
extern void tzpc_init(void);
int _main(unsigned int start, unsigned int sp1)
{
	unsigned int link_start, now;
	unsigned int i = 1;
	system_clock_init();
	init_ddr();	
	tzpc_init();
	code_relocate();
	asm("mov sp, #0x80000000\n");
	init_console();
	debug("memeory inited bl2 first at %X\n", start);
 	ibug("SP at %X\n", sp1);
	
	link_start = get_start();
	debug("FIRST INS = %X\n", VA(0x40000000));
	debug("GPM4CON = %X\n", GPM4CON);
	now = current_pc();
	debug("current= %X\n", now);
	unsigned char *p = (unsigned char *)0x02020000;
	memcpy2(p, "Hello kevin", 12);
	debug("get: %s\n", p);
	
#if 0
	system_clock_init();
	init_ddr();	
	debug("memeory inited\n");
	tzpc_init();	
	code_relocate();
	link_start = get_start();
#endif	
	debug("READ data at %X\r\n", VA(0X40002000) /*link_start*/);
//	init_console();
	for (;;mdelay(1000),i++) {
		show_led(i);
//		debug("hello kevin %d\r\n", i);
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


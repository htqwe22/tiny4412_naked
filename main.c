#include "console.h"
#include "util.h"
#include "shell.h"
#include "kv_string.h"
#include "util_string.h"
#include "mmu.h"


#define GPM4CON (*(volatile unsigned int *)0x110002e0)
#define GPM4DAT (*(volatile unsigned int *)0x110002e4)
// key 
#define GPX3CON (*(volatile unsigned int *)0x11000c60)
#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

void mdelay(unsigned time);
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
extern void set_sp(void);
int _main(unsigned int start, unsigned int sp1)
{
	unsigned int link_start, now;
	unsigned int i = 1;
	system_clock_init();	
	show_led(6);
	init_ddr();	
	show_led(15);
	tzpc_init();
	code_relocate();	
	show_led(8);
	asm("mov sp, #0x80000000\n"); 
//	set_sp();

	init_console();
	ibug("\nboot at %#X\n", get_link_addr());
	init_base_page();
	enable_mmu();
	ibug("open mmu\n");
//	debug("memeory inited bl2 first at %X\n", start);
// 	ibug("SP at %X\n", sp1);
//	link_start = get_start();
//	debug("FIRST INS = %X\n", VA(0x40000000));
//	debug("GPM4CON = %X\n", GPM4CON);
//	now = current_pc();
//	debug("current= %X\n", now);
//	unsigned char *p = (unsigned char *)0x02020000;
//	kv_memcpy(p, "Hello kevin", 12);
//	debug("get: %s\n", p);

#if 0
	system_clock_init();
	init_ddr();	
	debug("memeory inited\n");
	tzpc_init();	
	code_relocate();
	link_start = get_start();
#endif	
//	VA(0x30000000) = 0x80;	//这个地址应该是不能使用的，没有映射
//	asm("swi #5");
//	debug("READ data at %X\r\n", VA(0X0) /*link_start*/);
//	debug("len = %d\n", kv_strlen("hello world"));
	
#if 0	
	debug("%d \n", kv_memcmp(d, "hello worod", 12));
	char *p = kv_strchr(d, 'k');
	if (p) {
		debug("found at %p, is %c\n", p, *p);
	}else{
		debug("not found\n");
	}
#endif		
	int ch;
	for (;;) {
		do_shell_loop();
	}
	return 0;	
}
#if 0
void mdelay(unsigned time)
{
	for (; time > 0; time--) {
		tick_count(135000);
	}
}
#endif


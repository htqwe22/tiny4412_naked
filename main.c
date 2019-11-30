#include "console.h"
#include "util.h"
#include "shell.h"
#include "kv_string.h"
#include "util_string.h"
#include "mmu.h"
#include "exception.h"
#include "timer.h"
#include "task.h"
#include "kv_usb.h"

#define BOOT_ADDR	0x60000000

#define GPM4CON (*(volatile unsigned int *)0x110002e0)
#define GPM4DAT (*(volatile unsigned int *)0x110002e4)
// key 
//#define GPX3CON (*(volatile unsigned int *)0x11000c60)
//#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

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
extern void dcache_open();
void* task_fun(void *arg);

static void my_timer_fun(unsigned long args);
uint32_t stack[500];
struct timer_args
{
	uint32_t times;
};
static struct timer_args my_args;

int _main(unsigned int start, unsigned int sp1)
{
	unsigned int link_start, now;
	unsigned int i = 1;
//	show_led(6);
	link_start = get_link_addr();

	if (link_start == BOOT_ADDR) {
		system_clock_init();	
		init_ddr(); 
		tzpc_init();
	}

	code_relocate();
	dcache_open();
	asm("mov sp, #0x80000000\n"); 
//	set_sp();

	init_console();
//	debug_clk_regs(1);

	ibug("\nboot at %#X\n", link_start);
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

//	VA(0x30000000) = 0x80;	//这个地址应该是不能使用的，没有映射
	ibug("SP is %#X\n", get_sp());
	enable_irq_fiq();
	gpio_irq_test();
	start_sys_timer(1);
//	int timer_id = start_soft_timer(1000, my_timer_fun , (unsigned long)&my_args);
//	ibug("get timer_id %d\n", timer_id);
//	asm("swi #5");
//	debug("READ data at %X\r\n", VA(0X0) /*link_start*/);
//	debug("len = %d\n", kv_strlen("hello world"));
	debug("SP is %#X\n", get_sp());
	int ch;
//	init_task();
//	task_id_t tid = kv_create_task("kevin", task_fun, NULL, stack, 500);
	usb_init();
	for (;;) {
		do_shell_loop();
		uart_print_tx_fifo(100);
	}
	return 0;	
}


void* task_fun(void *arg)
{
	debug("hello world %d\n",1111);
}


static void my_timer_fun(unsigned long args)
{
	struct timer_args *p_args = (struct timer_args *)args;	
	debug("hello world %d\n", ++p_args->times);
}


#if 0
void mdelay(unsigned time)
{
	for (; time > 0; time--) {
		tick_count(135000);
	}
}
#endif


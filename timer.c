
/**********************************************************************************
 * FILE : timer.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-11 , At 23:08:45
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "timer.h"
#include "exception.h"
#include "util.h"


#define SOFT_TIMER_NUM	5
struct soft_timer
{
	void (*timer_fun)(unsigned long args);
	unsigned long args;
	uint32_t period_ms;
	uint32_t triggle_tick;
};


struct soft_timer g_timers[SOFT_TIMER_NUM];


static uint32_t tick_cnt;

int start_soft_timer(uint32_t period_ms, void (*timer_fun)(unsigned long args), unsigned long args)
{
	int i;
	for (i = 0; i < SOFT_TIMER_NUM; i++)
	{
		if (!g_timers[i].timer_fun) 
		{
			disable_irq();
			g_timers[i].timer_fun = timer_fun;
			g_timers[i].period_ms = period_ms;			
			g_timers[i].args = args;			
			g_timers[i].triggle_tick = tick_cnt + period_ms;
			enable_irq();
			return i;
		}
	}
	return -1;
}

int mod_soft_timer(int timer_id, uint32_t new_period_ms)
{
	if (g_timers[timer_id].timer_fun) {
		disable_irq();
		g_timers[timer_id].triggle_tick = tick_cnt + new_period_ms;
		g_timers[timer_id].period_ms = new_period_ms;
		enable_irq();
	}

}

void stop_soft_timer(int timer_id)
{
	if (g_timers[timer_id].timer_fun) {
		disable_irq();
		g_timers[timer_id].timer_fun = NULL;
		enable_irq();
	}
}

void timer_irq_handler(void)
{
	int i;

	L0_INT_CSTAT = L0_INT_CSTAT;
	tick_cnt++;
	for (i = 0; i < SOFT_TIMER_NUM; i++) {
		if (g_timers[i].timer_fun && tick_cnt == g_timers[i].triggle_tick) {
			g_timers[i].timer_fun(g_timers[i].args);
			g_timers[i].triggle_tick = tick_cnt + g_timers[i].period_ms;
		}
	}
}

uint32_t get_sys_tick(void)
{
	return tick_cnt;
}

void start_sys_timer(uint32_t experiod_ms)
{
	uint32_t tmp;
	if (!experiod_ms)
		return;

	L0_INT_ENB = 1;

	
	MCT_CFG = 7; //8分频24M
//	MCT_CFG |= 0x7000; //8分频24M
	tmp = (24 * 1000/8 *experiod_ms) -1;
	L0_TCNTB = tmp;	
	while (L0_WSTAT & 1);	
	L0_WSTAT |= 1;
	
	L0_FRCNTB = tmp;
	L0_ICNTB = 0; //每个tick都中断
	while (L0_WSTAT & 2);
	L0_WSTAT |= 2;



	L0_TCON  |= 2;


	L0_TCON  |= 1;
	while (L0_WSTAT & 7);
	L0_WSTAT |= 7;

	L0_TCON  |= 0x4;
	
//	show_led(3);
	while (L0_WSTAT & 7);
	L0_WSTAT |= 7;


#if 0
		// 74号中断
	ICDISER_CPU(2, 0) |=  0x400; //在CPU0上使能74号中断

	// 设置哪个CPU来接受中断
	ICDIPTR_CPU(18, 0) |= 0x010000; //0101010101 表示ID为0-4的SGI发送给CPU0,这里的第二个参数是发送者CPU
#else
	enable_gic_irq_id(74);
#endif
	IESR4	= (1<<24);
}



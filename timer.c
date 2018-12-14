
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

static uint32_t tick_cnt;

void timer_irq_handler(void)
{
	static volatile uint32_t tmp_irq;
	tmp_irq = L0_INT_CSTAT;
	L0_INT_CSTAT = tmp_irq;	// clear
	tick_cnt++;
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

//	L0_TCON  |= 0xC;
	L0_TCON  |= 0x4;
	while (L0_WSTAT & 7);
	L0_WSTAT |= 7;


	enable_gic_irq_id(74);

		// 74号中断
//	ICDISER_CPU(2, 0) |=  0x400; //在CPU0上使能74号中断

	// 设置哪个CPU来接受中断
//	ICDIPTR_CPU(18, 0) |= 0x010000; //0101010101 表示ID为0-4的SGI发送给CPU0,这里的第二个参数是发送者CPU

	IESR4   = (1<<24);

}



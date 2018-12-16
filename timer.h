
/**********************************************************************************
 * FILE : timer.h
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-11 , At 23:08:45
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#ifndef KV_TIMER_H
#define KV_TIMER_H

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_BASE	0x10050000

#define MCT_CFG			VA(TIMER_BASE)
#define L0_TCNTB		VA(TIMER_BASE + 0X300)
#define L0_ICNTB		VA(TIMER_BASE + 0X308)
#define L0_FRCNTB		VA(TIMER_BASE + 0X310)
#define L0_TCON			VA(TIMER_BASE + 0X320)
#define L0_WSTAT		VA(TIMER_BASE + 0X340)
#define L0_INT_ENB		VA(TIMER_BASE + 0X334)
#define L0_INT_CSTAT	VA(TIMER_BASE + 0X330)
#define L0_TCNTO		VA(TIMER_BASE + 0X0300)
#define L0_FRCNTO		VA(TIMER_BASE + 0X030C)
#define IESR4			VA(0x10440000 + 0X40)
//#define ISTR4			VA(0x10440000 + 0X48)


void start_sys_timer(uint32_t experiod_ms);

uint32_t get_sys_tick(void);


int start_soft_timer(uint32_t period_ms, void (*timer_fun)(unsigned long args), unsigned long args);

int mod_soft_timer(int timer_id, uint32_t new_period_ms);

void stop_soft_timer(int timer_id);

#ifdef __cplusplus
}
#endif

#endif

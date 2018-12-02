#include "util.h"
#include "cpu.h"
extern void init_console(void);

// CMU_CPU
#define CLK_SRC_CPU (*(volatile unsigned int *)0x10044200)
#define CLK_DIV_CPU0 (*(volatile unsigned int *)0x10044500)
#define CLK_DIV_CPU1 (*(volatile unsigned int *)0x10044504)

// CMU_DMC
#define CLK_SRC_DMC (*(volatile unsigned int *)0x10040200)
#define CLK_DIV_DMC0 (*(volatile unsigned int *)0x10040500)
#define CLK_DIV_DMC1 (*(volatile unsigned int *)0x10040504)

// CMU_TOP
#define CLK_SRC_TOP0 (*(volatile unsigned int *)0x1003C210)
#define CLK_SRC_TOP1 (*(volatile unsigned int *)0x1003C214)
#define CLK_DIV_TOP (*(volatile unsigned int *)0x1003C510)

// CMU_LEFTBUS
#define CLK_SRC_LEFTBUS (*(volatile unsigned int *)0x10034200)
#define CLK_DIV_LEFTBUS (*(volatile unsigned int *)0x10034500)

// CMU_RIGHTBUS
#define CLK_SRC_RIGHTBUS (*(volatile unsigned int *)0x10038200)
#define CLK_DIV_RIGHTBUS (*(volatile unsigned int *)0x10038500)

// locktime
#define APLL_LOCK (*(volatile unsigned int *)0x10044000)
#define MPLL_LOCK (*(volatile unsigned int *)0x10044008)
#define EPLL_LOCK (*(volatile unsigned int *)0x1003C010)
#define VPLL_LOCK (*(volatile unsigned int *)0x1003C020)

// APLL
#define APLL_CON1 (*(volatile unsigned int *)0x10044104)
#define APLL_CON0 (*(volatile unsigned int *)0x10044100)

// MPLL
#define MPLL_CON0 (*(volatile unsigned int *)0x10040108)
#define MPLL_CON1 (*(volatile unsigned int *)0x1004010c)

// EPLL
#define EPLL_CON2 (*(volatile unsigned int *)0x1003C118)
#define EPLL_CON1 (*(volatile unsigned int *)0x1003C114)
#define EPLL_CON0 (*(volatile unsigned int *)0x1003C110)

// VPLL
#define VPLL_CON0 (*(volatile unsigned int *)0x1003C120)
#define VPLL_CON1 (*(volatile unsigned int *)0x1003C124)
#define VPLL_CON2 (*(volatile unsigned int *)0x1003C128)
#if 0
void debug_clk_regs(int index)
{
	ibug("\r\n=========== CMU_CPU ============\r\n");
	ibug("CLK_SRC_CPU:%08X\r\n", CLK_SRC_CPU);
	ibug("CLK_DIV_CPU0:%08X\r\n", CLK_DIV_CPU0);
	ibug("CLK_DIV_CPU1:%08X\r\n", CLK_DIV_CPU1);

	ibug("=========== CMU_DMC ============\r\n");
	ibug("CLK_SRC_DMC:%08X\r\n", CLK_SRC_DMC);
	ibug("CLK_DIV_DMC0:%08X\r\n", CLK_DIV_DMC0);
	ibug("CLK_DIV_DMC1:%08X\r\n", CLK_DIV_DMC1);

	ibug("=========== CMU_TOP ============\r\n");
	ibug("CLK_SRC_TOP0:%08X\r\n", CLK_SRC_TOP0);
	ibug("CLK_SRC_TOP1:%08X\r\n", CLK_SRC_TOP1);
	ibug("CLK_DIV_TOP:%08X\r\n", CLK_DIV_TOP);

	
	ibug("=========== PLL_LOCK ============\r\n");
	ibug("APLL_LOCK:%08X\r\n", APLL_LOCK);
	ibug("MPLL_LOCK:%08X\r\n", MPLL_LOCK);
	ibug("EPLL_LOCK:%08X\r\n", EPLL_LOCK);
	ibug("VPLL_LOCK:%08X\r\n", VPLL_LOCK);
	
	ibug("=========== APLL_CON ============\r\n");
	ibug("APLL_CON0:%08X\r\n", APLL_CON0);
	ibug("APLL_CON1:%08X\r\n", APLL_CON1);
	
	ibug("=========== MPLL_CON ============\r\n");
	ibug("MPLL_CON0:%08X\r\n", MPLL_CON0);
	ibug("MPLL_CON1:%08X\r\n", MPLL_CON1);
	
	ibug("=========== EPLL_CON ============\r\n");
	ibug("EPLL_CON0:%08X\r\n", EPLL_CON0);
	ibug("EPLL_CON1:%08X\r\n", EPLL_CON1);
	ibug("EPLL_CON2:%08X\r\n", EPLL_CON2);
	
	ibug("=========== VPLL_CON ============\r\n");
	ibug("VPLL_CON0:%08X\r\n", VPLL_CON0);
	ibug("VPLL_CON1:%08X\r\n", VPLL_CON1);
	ibug("VPLL_CON2:%08X\r\n", VPLL_CON2);
	
	ibug("--------------- L I N E [%d] -----------------------\r\n", index);
}
#endif

static clock_init(void)
{
//	debug_clk_regs(1);

//	debug_clk_regs(2);
}



void system_clock_init(void)
{
	// CLK_SRC_CPU = 0 , Set CPU to 24M
	CLK_SRC_CPU = (0);
	// delay.
	tick_count(0x10000);
	// CMU_CPU MUX / DIV
	CLK_DIV_DMC0 = CLK_DIV_DMC0_VAL;
	CLK_DIV_DMC1 = CLK_DIV_DMC1_VAL;

	// CMU_TOP MUX / DIV
	CLK_SRC_TOP0 = CLK_SRC_TOP0_VAL;
	CLK_SRC_TOP1 = CLK_SRC_TOP1_VAL;
	tick_count(0x10000);

	CLK_DIV_TOP = CLK_DIV_TOP_VAL;

	// CMU_LEFTBUS MUX / DIV
	CLK_SRC_LEFTBUS = CLK_SRC_LEFTBUS_VAL;
	tick_count(0x10000);
	CLK_DIV_LEFTBUS = CLK_DIV_LEFRBUS_VAL;

	// CMU_RIGHTBUS MUX / DIV
	CLK_SRC_RIGHTBUS = CLK_SRC_RIGHTBUS_VAL;
	tick_count(0x10000);
	CLK_DIV_RIGHTBUS = CLK_DIV_RIGHTBUS_VAL;

	// Set PLL locktime
	APLL_LOCK = APLL_LOCK_VAL;
	MPLL_LOCK = MPLL_LOCK_VAL;
	EPLL_LOCK = EPLL_LOCK_VAL;
	VPLL_LOCK = VPLL_LOCK_VAL;

	CLK_DIV_CPU0 = CLK_DIV_CPU0_VAL;
	CLK_DIV_CPU1 = CLK_DIV_CPU1_VAL;

	// @ Set APLL
	APLL_CON1 = APLL_CON1_VAL;
	APLL_CON0 = APLL_CON0_VAL;
	
	if (MPLL_CON0 == 0xA0640301) 
	{
//		show_led(6);
		MPLL_CON1 = MPLL_CON1_VAL;
		MPLL_CON0 = MPLL_CON0_VAL;
	}
	// SKEP_MPLL
	// @ Set EPLL
	EPLL_CON2 = EPLL_CON2_VAL;
	EPLL_CON1 = EPLL_CON1_VAL;
	EPLL_CON0 = EPLL_CON0_VAL;

	// @ Set VPLL
	VPLL_CON2 = VPLL_CON2_VAL;
	VPLL_CON1 = VPLL_CON1_VAL;
	VPLL_CON0 = VPLL_CON0_VAL;
	tick_count(0x40000);

	CLK_SRC_CPU = 0x01000001;
	CLK_SRC_DMC = 0x00011000;
	CLK_SRC_TOP0 = 0x00000110;
	CLK_SRC_TOP1 = 0x01111000;
	tick_count(0x40000);

}



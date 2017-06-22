#include "util.h"
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

void system_clock_init(void)
{
#if 1
	/*Set CPU to 24M, for safety*/
	debug_clk_regs(1);

	CLK_SRC_CPU = (0);
	init_console();
	// Set APLL 

	/* 设置APLL推荐设置到1400M
	 * APLL MPCore Corsight, HPM的时钟源
	 * 我们现在只设置CPU的频率提高，让灯闪得更快点，因为此时代码运行在IRAM中，所以我们应该可以
	 * 不用管其他的时钟，不知道IRAM与CPU的频率会不会有什么关系，先把问题留在这里。
	 * 第一按照时钟树，时钟源为FIN(pll)=24M（USBXIT）
	 * 参考步骤：p459
	 * 1. 设置PMS PLL_CON0[31:0]
	 * 2. 改变其他PLL控制值PLL_CON1[31:0]
	 * 3. 设置锁定时间，等时钟锁定
	 * 4. (等待)MUX_APLL_SEL = 1 。当PLL的输出稳定后，设置PLL的输出
	 */
	// PMS=(3, 175, 0) p451 ; 
	// 建议先把锁定时间设置了 270 cycles *PDIV, 1 cycle = 1/FREF=1/(FIN/PDIV) 
	APLL_LOCK = 3*270;
	
	APLL_CON0 = (3<<8) | (175<<16) | (0<<0) ; //| (1<<31);
	APLL_CON1 = 0x803800;
	
	APLL_CON0 |= 1<<31;
	while (APLL_CON0 & (1<<29) == 0) ;


	// 设置分频参数，然后切换时钟
	/*参考P449时钟关系那一小节，对时钟的关系有说明
	  所以对于
	  ACLK_COREM0 = 350M，所以COREM0_RATIO值为4-1
	  ACLK_COREM1 = 188, 所以COREM1_RATIO = 8-1
	  PERIPHCLK = 1400 所以PERIPH_RATIO = 0
	  ATCLK = 214, ATB_RATIO = 7-1
	  PCLK_DBG = 107 = ATCLK/(PCLK_DBG_RATIO + 1),所以PCLK_DBG_RATIO = 1
	  SCLKAPLL = MOUTAPLL/(APLL_RATIO + 1) = 没有指明是多少，先按网上设置为2吧
	*/
	CLK_DIV_CPU0 = (0<<0) | (3<<4) |(7<<8)| (0<<12) | (6<<16) | (1<<20) | (2<<24) | (0<< 28);
//	CLK_DIV_CPU0 = ((0<<28) | (2<<24) | (1<<20) | (6<<16) | (7<<12) | (7<<8) | (3<<4) | 0);



	/*
	  DOUTCOPY = MOUTHPM/(COPY_RATIO + 1)=200,但是要先选中 MUXHPM在CLK_SRC_CPU 中bit20选中0
	  所以设置COPY_RATIO = 6 HPM_RATIO = 0
	  ACLK_CORES = ARMCLK/(CORES_RATIO + 1) = 
	*/
	CLK_DIV_CPU1 = 6 | (0<<4) | (5<<8);

	CLK_SRC_CPU = 1 | (0<<24);
	debug_clk_regs(2);
#endif
}



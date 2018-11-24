#include "util.h"
#include "cpu.h"

#define CONFIG_IV_SIZE 0x1F
#define MCLK_400

static memory_init(void)
{
	uint32_t tmp;
	VA(0x10010350) = 1;
/*****************************************************************/
/*DREX0***********************************************************/
/*****************************************************************/
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	VA(APB_DMC_0_BASE+DMC_PHYZQCONTROL) = 0xE3854C03;
	tick_count(0x100000);
	
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL1) = 0xe000008e;
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL1) = 0xe0000086;

	VA(APB_DMC_0_BASE+DMC_PHYCONTROL0) = 0x71101008;
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL0) = 0x7110100A;
	
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL0) = 0x7110100B;
	
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL2) = 0x00000000;
	
	VA(APB_DMC_0_BASE+DMC_CONCONTROL) = 0x0FFF301A;
	VA(APB_DMC_0_BASE+DMC_MEMCONTROL) = 0x00312640;

	VA(APB_DMC_0_BASE+DMC_MEMCONFIG0) = 0x40e01323;
	VA(APB_DMC_0_BASE+DMC_MEMCONFIG1) = 0x60e01323;
	
#ifdef CONFIG_IV_SIZE
		tmp = 0x80000000 | CONFIG_IV_SIZE;
#else
		tmp = 0x08
#endif
	VA(APB_DMC_0_BASE+DMC_IVCONTROL) = tmp;

	VA(APB_DMC_0_BASE+DMC_PRECHCONFIG) = 0xff000000;

	// @TimingAref
	VA(APB_DMC_0_BASE+DMC_TIMINGAREF) = 0x000000BB;

#ifdef MCLK_330
	ldr	r1, =0x3545548d
	str	r1, [r0, #DMC_TIMINGROW]
	ldr	r1, =0x45430506
	str	r1, [r0, #DMC_TIMINGDATA]
	ldr	r1, =0x46000A3c
	str	r1, [r0, #DMC_TIMINGPOWER]
#endif
#ifdef MCLK_400
	//@TimingRow
	VA(APB_DMC_0_BASE+DMC_TIMINGROW) = 0x4046654f;
	//@TimingData
	VA(APB_DMC_0_BASE+DMC_TIMINGDATA) = 0x46400506;
	//@TimingPower
	VA(APB_DMC_0_BASE+DMC_TIMINGPOWER) = 0x52000a3c;
#endif	

	/* chip 0 */
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x07000000;
	tick_count(0x100000);
	
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00020000;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00030000;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00010002;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00000328;
	tick_count(0x100000);
	
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x0a000000;
	tick_count(0x100000);
	
	/* chip 0 */
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x07100000;
	tick_count(0x100000);
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00120000;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00130000;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00110002;
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x00100328;
	tick_count(0x100000);
	
	VA(APB_DMC_0_BASE+DMC_DIRECTCMD) = 0x0a100000;
	VA(APB_DMC_0_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	tick_count(0x100000);
	
	/*****************************************************************/
	/*DREX1***********************************************************/
	/*****************************************************************/
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	VA(APB_DMC_1_BASE+DMC_PHYZQCONTROL) = 0xE3854C03;
	tick_count(0x100000);

	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe000008e;
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL0) = 0x71101008;
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL0) = 0x7110100A;
	
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe0000086;
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL0) = 0x7110100B;
	
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL2) = 0x00000000;
	
	VA(APB_DMC_1_BASE+DMC_CONCONTROL) = 0x0FFF301A;
	VA(APB_DMC_1_BASE+DMC_MEMCONTROL) = 0x00312640;

	// @Interleaved?
	VA(APB_DMC_1_BASE+DMC_MEMCONFIG0) = 0x40e01323;
	VA(APB_DMC_1_BASE+DMC_MEMCONFIG1) = 0x60e01323;	
	
#ifdef CONFIG_IV_SIZE
		tmp =(0x80000000 | CONFIG_IV_SIZE);
#else
		tmp =0x08;
#endif
	VA(APB_DMC_1_BASE+DMC_IVCONTROL) = tmp; 

	VA(APB_DMC_1_BASE+DMC_PRECHCONFIG) = 0xff000000; 
	//@TimingAref
	VA(APB_DMC_1_BASE+DMC_TIMINGAREF) = 0x000000BB; 
	
#ifdef MCLK_330
	ldr r1, =0x3545548d
	str r1, [r0, #DMC_TIMINGROW]
	ldr r1, =0x45430506
	str r1, [r0, #DMC_TIMINGDATA]
	ldr r1, =0x46000A3c
	str r1, [r0, #DMC_TIMINGPOWER]
#endif
#ifdef MCLK_400
	//@TimingRow
	VA(APB_DMC_1_BASE+DMC_TIMINGROW) = 0x4046654f; 
	//@TimingData
	VA(APB_DMC_1_BASE+DMC_TIMINGDATA) = 0x46400506; 
	//@TimingPower
	VA(APB_DMC_1_BASE+DMC_TIMINGPOWER) = 0x52000a3c;
#endif
	/* chip 0 */
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x07000000;
	tick_count(0x100000);

	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00020000;
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00030000;
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00010002;
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00000328;
	tick_count(0x100000);
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x0a000000;
	tick_count(0x100000);
	
	/* chip 1 */
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x07100000;	
	tick_count(0x100000);
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00120000;
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00130000;
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00110002;	
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x00100328;	
	tick_count(0x100000);
	
	VA(APB_DMC_1_BASE+DMC_DIRECTCMD) = 0x0a100000;	
	tick_count(0x100000);
	
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe000008e;	
	VA(APB_DMC_1_BASE+DMC_PHYCONTROL1) = 0xe0000086;	
	tick_count(0x100000);
	
	/*****************************************************************/
	/*Finalize********************************************************/
	/*****************************************************************/

	VA(APB_DMC_0_BASE+DMC_CONCONTROL) = 0x0FFF303A;	
	VA(APB_DMC_1_BASE+DMC_CONCONTROL) = 0x0FFF303A;
}
void init_ddr(void)
{

#if 1
	memory_init();
#else

	/**
	 *  1: half_sync
	 *  0: full_sync 
	 */

	 VA(0x10010350) = 1;
	
	/*DREX0***********************************************************/
	PHYCONTROL1	= 0xe0000086;
	PHYZQCONTROL = 0xE3854C03;
	debug();
	delay(0x100000);

	PHYCONTROL1 = 0xe000008e;
	PHYCONTROL1 = 0xe0000086;

	PHYCONTROL0 = 0x71101008;
	PHYCONTROL0 = 0x7110100A;

	PHYCONTROL1 = 0xe0000086;
	PHYCONTROL0 = 0x7110100B;

	PHYCONTROL2 = 0;

	CONCONTROL = 0x0FFF301A;
	MEMCONTROL = 0x00312640;

	MEMCONFIG0 = 0x40e01323;
	MEMCONFIG1 = 0x60e01323;

	IVCONTROL =  0x80000000 | 0x1f;

	PRECHCONFIG = 0xff000000;
	TIMINGAREF = 0x000000BB;
	
	TIMINGROW = 0x4046654f;
	TIMINGDATA = 0x46400506;
	TIMINGPOWER = 0x52000a3c;

	DIRECTCMD = 0x07000000;
	delay(0x100000);
	debug();
	DIRECTCMD = 0x00020000;
	DIRECTCMD = 0x00030000;
	DIRECTCMD = 0x00010002;
	DIRECTCMD = 0x00000328;
	delay(0x100000);
	debug();
	DIRECTCMD = 0x0a000000;
	delay(0x100000);
	debug();
	DIRECTCMD = 0x07100000;
	delay(0x100000);
	debug();
	DIRECTCMD = 0x00120000;
	DIRECTCMD = 0x00130000;
	DIRECTCMD = 0x00110002;
	DIRECTCMD = 0x00100328;
	delay(0x100000);
	debug();
	DIRECTCMD = 0x0a100000;
	delay(0x100000);
	debug();
	PHYCONTROL1 = 0xe000008e;
	PHYCONTROL1 = 0xe0000086;
	delay(0x100000);
	debug();
	/*DREX1***********************************************************/
	// ...
	CONCONTROL = 0x0FFF303A;
	debug();
#endif	
}




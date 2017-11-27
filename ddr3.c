#include "util.h"
#include "ddr3.h"
static void delay(unsigned d)
{
	for (;d--;);
}
void init_ddr(void)
{
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
}




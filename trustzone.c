
/**********************************************************************************
 * FILE : trustzone.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-11-24 , At 11:39:17
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "trustzone.h"
#include "util.h"
#include "cpu.h"
void tzpc_init(void)
{
	VA(ELFIN_TZPC0_BASE) = 0;
	
	VA(ELFIN_TZPC0_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC0_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC0_BASE + TZPC_DECPROT2SET_OFFSET) = 0xbd;	
	VA(ELFIN_TZPC0_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;

	VA(ELFIN_TZPC1_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC1_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC1_BASE + TZPC_DECPROT2SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC1_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;

	VA(ELFIN_TZPC2_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC2_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC2_BASE + TZPC_DECPROT2SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC2_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;

	VA(ELFIN_TZPC3_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC3_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC3_BASE + TZPC_DECPROT2SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC3_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;

	VA(ELFIN_TZPC4_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC4_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC4_BASE + TZPC_DECPROT2SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC4_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;

	VA(ELFIN_TZPC5_BASE + TZPC_DECPROT0SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC5_BASE + TZPC_DECPROT1SET_OFFSET) = 0xff;
	VA(ELFIN_TZPC5_BASE + TZPC_DECPROT2SET_OFFSET) = 0xff;	
	VA(ELFIN_TZPC5_BASE + TZPC_DECPROT3SET_OFFSET) = 0xff;
}







/**********************************************************************************
 * FILE : exception.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-04 , At 01:18:38
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "exception.h"
#include "util.h"

void show_current_sp(unsigned long sp, unsigned long lr)
{
	ibug("SP:0x%08X 0x%08X\n", sp, lr);
}

void exception_undefined_instruction(unsigned long lr)
{

}

void exception_software_interrupt(unsigned long lr, unsigned long index)
{
	ibug("LR:0x%08X %u\n", lr, index);
}
	
void exception_prefetch_abort(unsigned long lr)
{

}

void exception_data_abort(unsigned long lr)
{

}

void exception_irq(unsigned long lr)
{

}

void exception_fiq(unsigned long lr)
{

}



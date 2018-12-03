
/**********************************************************************************
 * FILE : exception.h
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-04 , At 01:18:38
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#ifndef KV_EXCEPTION_H
#define KV_EXCEPTION_H

#ifdef __cplusplus
extern "C" {
#endif



unsigned long get_sp();

void show_current_sp(unsigned long sp, unsigned long lr);

void exception_undefined_instruction(unsigned long lr);

void exception_software_interrupt(unsigned long lr, unsigned long index);
	
void exception_prefetch_abort(unsigned long lr);

void exception_data_abort(unsigned long lr);

void exception_irq(unsigned long lr);

void exception_fiq(unsigned long lr);




#ifdef __cplusplus
}
#endif

#endif

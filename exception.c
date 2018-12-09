
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

#define GIC_BASE		0x10480000
#define ICCICR_CPU0		VA(GIC_BASE)
#define ICCICR_CPU1		VA(GIC_BASE+0x4000)
#define ICCICR_CPU2		VA(GIC_BASE+0x8000)
#define ICCICR_CPU3		VA(GIC_BASE+0xc000)

#define ICCPMR_CPU0		VA(GIC_BASE + 0x0004)
#define ICCPMR_CPU1		VA(GIC_BASE + 0x4004)
#define ICCPMR_CPU2		VA(GIC_BASE + 0x8004)
#define ICCPMR_CPU3		VA(GIC_BASE + 0xC004)



#define ICCBPR_CPU0		VA(GIC_BASE + 0x0008)
#define ICCBPR_CPU1		VA(GIC_BASE + 0x4008)
#define ICCBPR_CPU2		VA(GIC_BASE + 0x8008)
#define ICCBPR_CPU3		VA(GIC_BASE + 0xC008)

#define ICCIAR_CPU0		VA(GIC_BASE + 0x000C)
#define ICCIAR_CPU1		VA(GIC_BASE + 0x400C)
#define ICCIAR_CPU2		VA(GIC_BASE + 0x800C)
#define ICCIAR_CPU3		VA(GIC_BASE + 0xC00C)


#define ICCRPR_CPU0		VA(GIC_BASE + 0x0014)
#define ICCRPR_CPU1		VA(GIC_BASE + 0x4014)
#define ICCRPR_CPU2		VA(GIC_BASE + 0x8014)
#define ICCRPR_CPU3		VA(GIC_BASE + 0xc014)

#define ICCHPIR_CPU0		VA(GIC_BASE + 0x0018)
#define ICCHPIR_CPU1		VA(GIC_BASE + 0x4018)
#define ICCHPIR_CPU2		VA(GIC_BASE + 0x8018)
#define ICCHPIR_CPU3		VA(GIC_BASE + 0xc018)

#define ICCABPR_CPU0		VA(GIC_BASE + 0x001c)
#define ICCABPR_CPU1		VA(GIC_BASE + 0x401c)
#define ICCABPR_CPU2		VA(GIC_BASE + 0x801c)
#define ICCABPR_CPU3		VA(GIC_BASE + 0xc01c)

#define ICDDCR				VA(0x10490000)
#define ICDICTR				VA(0x10490004)
#define ICDIIDR				VA(0x10490008)


#define ICDISR0_CPU0		VA(0x10490000 + 0x0080)
#define ICDISR1_CPU0		VA(0x10490000 + 0x0084)
#define ICDISR2_CPU0		VA(0x10490000 + 0x0088)
#define ICDISR3_CPU0		VA(0x10490000 + 0x008c)
#define ICDISR4_CPU0		VA(0x10490000 + 0x0090)
#define ICDISR0_CPU1		VA(0x10490000 + 0x4080)
#define ICDISR0_CPU2		VA(0x10490000 + 0x8080)
#define ICDISR0_CPU3		VA(0x10490000 + 0xc080)

#define ICDISER0_CPU0		VA(0x10490000 + 0x0100)
#define ICDISER1_CPU0		VA(0x10490000 + 0x0104)
#define ICDISER2_CPU0		VA(0x10490000 + 0x0108)
#define ICDISER3_CPU0		VA(0x10490000 + 0x010c)
#define ICDISER4_CPU0		VA(0x10490000 + 0x0110)
#define ICDISER0_CPU1		VA(0x10490000 + 0x4110)
#define ICDISER0_CPU2		VA(0x10490000 + 0x8110)
#define ICDISER0_CPU3		VA(0x10490000 + 0xc110)


#define ICDICER0_CPU0		VA(0x10490000 + 0x0180)
#define ICDICER1_CPU0		VA(0x10490000 + 0x0184)
#define ICDICER2_CPU0		VA(0x10490000 + 0x0188)
#define ICDICER3_CPU0		VA(0x10490000 + 0x018c)
#define ICDICER4_CPU0		VA(0x10490000 + 0x0190)
#define ICDICER0_CPU1		VA(0x10490000 + 0x4180)
#define ICDICER0_CPU2		VA(0x10490000 + 0x8180)
#define ICDICER0_CPU3		VA(0x10490000 + 0xc180)

#define ICDISPR0_CPU0		VA(0x10490000 + 0x0200)
#define ICDISPR1_CPU0		VA(0x10490000 + 0x0204)
#define ICDISPR2_CPU0		VA(0x10490000 + 0x0208)
#define ICDISPR3_CPU0		VA(0x10490000 + 0x020c)
#define ICDISPR4_CPU0		VA(0x10490000 + 0x0210)
#define ICDISPR0_CPU1		VA(0x10490000 + 0x4200)
#define ICDISPR0_CPU2		VA(0x10490000 + 0x8200)
#define ICDISPR0_CPU3		VA(0x10490000 + 0xc200)


#define ICDICPR0_CPU0		VA(0x10490000 + 0x0280)
#define ICDICPR1_CPU0		VA(0x10490000 + 0x0284)
#define ICDICPR2_CPU0		VA(0x10490000 + 0x0288)
#define ICDICPR3_CPU0		VA(0x10490000 + 0x028C)
#define ICDICPR4_CPU0		VA(0x10490000 + 0x0290)
#define ICDICPR0_CPU1		VA(0x10490000 + 0x4280)
#define ICDICPR0_CPU2		VA(0x10490000 + 0x8280)
#define ICDICPR0_CPU3		VA(0x10490000 + 0xc280)

#define ICDABR0_CPU0		VA(0x10490000 + 0x0300)
#define ICDABR1_CPU0		VA(0x10490000 + 0x0304)
#define ICDABR2_CPU0		VA(0x10490000 + 0x0308)
#define ICDABR3_CPU0		VA(0x10490000 + 0x030C)
#define ICDABR4_CPU0		VA(0x10490000 + 0x0310)
#define ICDABR0_CPU1		VA(0x10490000 + 0x4300)
#define ICDABR0_CPU2		VA(0x10490000 + 0x8300)
#define ICDABR0_CPU3		VA(0x10490000 + 0xC300)

#define PPI_STATUS_CPU0		VA(0x10490000 + 0x0D00)
#define PPI_STATUS_CPU1		VA(0x10490000 + 0x4D00)
#define PPI_STATUS_CPU2		VA(0x10490000 + 0x8D00)
#define PPI_STATUS_CPU3		VA(0x10490000 + 0xcD00)

#define ICDSGIR				VA(0x10490000 + 0x0F00)

#define INTEG_EN_C_CPU0		VA(GIC_BASE + 0x40)
#define INTERRUPT_OUT_CPU0	VA(GIC_BASE + 0x44)
#define ICCIIDR				VA(GIC_BASE + 0xFC)

void enable_irq_fiq(void)
{
	asm(
		"mrs r0, cpsr\n"
		"bic r0, #0xC0\n"
		"msr cpsr, r0\n"
	);
}


void open_ICCICR(void)
{
	unsigned long tmp;
	tmp = ICCICR_CPU0;
	tmp |= 1;
	ICCICR_CPU0 = tmp;

	tmp = ICCICR_CPU1;
	tmp |= 1;
	ICCICR_CPU1 = tmp;
	
	tmp = ICCICR_CPU2;
	tmp |= 1;
	ICCICR_CPU2 = tmp;
	
	tmp = ICCICR_CPU3;
	tmp |= 1;
	ICCICR_CPU3 = tmp;
}

void set_ICCPMR(void)
{
	unsigned long tmp;
	tmp = ICCPMR_CPU0;
	tmp |= 0xff;
	ICCPMR_CPU0 = tmp;

	tmp = ICCPMR_CPU1;
	tmp |= 0xff;
	ICCPMR_CPU1 = tmp;
	
	tmp = ICCPMR_CPU2;
	tmp |= 0xff;
	ICCPMR_CPU2 = tmp;
	
	tmp = ICCPMR_CPU3;
	tmp |= 0xff;
	ICCPMR_CPU3 = tmp;
}

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



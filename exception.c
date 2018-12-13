
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

extern void timer_irq_handler(void);
extern uint32_t get_sys_tick(void);


void exception_irq(unsigned long lr)
{
	unsigned long tmp;
	static uint32_t counts;
	uint8_t cpu, irq_id;
	tmp = ICCIAR_CPU(0);
	cpu = (tmp>>10) & 7;
	irq_id = tmp & 0x1FF;
		// 清除中断
//	ibug("from %d, irq %d\n", cpu, irq_id);

//	ibug("PEND %X\n", EXT_INT43_PEND);
	tmp = EXT_INT43_PEND;
	if (tmp) {
		ibug("from %d, irq %d\n", cpu, irq_id);
		ibug("PEND %X\n", tmp);
		EXT_INT43_PEND = tmp;
	}
	tmp = L0_INT_CSTAT;	
	if (tmp)
	{
		timer_irq_handler();			
		L0_INT_CSTAT = tmp;		
		if (get_sys_tick() - counts >= 1000) {
			counts = get_sys_tick();
			ibug("1 S\n");
		}
	}
	
	ICCEOIR_CPU(0) = irq_id;

}

void exception_fiq(unsigned long lr)
{
	ibug("fiq\n");
}

void enable_irq_fiq(void)
{
	asm(
		"mrs r0, cpsr\n"
		"bic r0, #0xC0\n"
		"msr cpsr, r0\n"
	);
	/* or cpise i
	*/
}


void open_ICCICR(void)
{
	unsigned long tmp;
	tmp = ICCICR_CPU(0);
	tmp |= 1;
	ICCICR_CPU(0) = tmp;

	tmp = ICCICR_CPU(1);
	tmp |= 1;
	ICCICR_CPU(1) = tmp;
	
	tmp = ICCICR_CPU(2);
	tmp |= 1;
	ICCICR_CPU(2) = tmp;
	
	tmp = ICCICR_CPU(3);
	tmp |= 1;
	ICCICR_CPU(3) = tmp;
}

void set_ICCPMR(void)
{
	unsigned long tmp;
	tmp = ICCPMR_CPU(0);
	tmp |= 0xff;
	ICCPMR_CPU(0) = tmp;

	tmp = ICCPMR_CPU(1);
	tmp |= 0xff;
	ICCPMR_CPU(1) = tmp;
	
	tmp = ICCPMR_CPU(2);
	tmp |= 0xff;
	ICCPMR_CPU(2) = tmp;
	
	tmp = ICCPMR_CPU(3);
	tmp |= 0xff;
	ICCPMR_CPU(3) = tmp;
}

/* 设置组级优先级
 * 取值7~0，至少一个子优先级
 */
void set_ICCBPR(uint8_t group_bits)
{
	unsigned long tmp;
	group_bits = 7-group_bits;
	tmp = ICCBPR_CPU(0);
	tmp |= group_bits;
	ICCBPR_CPU(0) = tmp;

	tmp = ICCBPR_CPU(1);
	tmp |= group_bits;
	ICCBPR_CPU(1) = tmp;
	
	tmp = ICCBPR_CPU(2);
	tmp |= group_bits;
	ICCBPR_CPU(2) = tmp;
	
	tmp = ICCBPR_CPU(3);
	tmp |= group_bits;
	ICCBPR_CPU(3) = tmp;
}



void open_ICDDCR(void)
{
	unsigned long tmp;
	tmp = ICDDCR;
	tmp |= 1;
	ICDDCR = tmp;
}

void SGI_test(void)
{
	debug("test gic\n");
	open_ICCICR(); //使能中断	
	ICDISER_CPU(0, 0) = 0xFFFF; //在CPU0上使能0~15号中断
	ICDISER_CPU(0, 1) = 0xFFFF; //在CPU1上使能0~15号中断
	open_ICDDCR();	//允许所有外设中断
	
	set_ICCPMR();	// 设置中断优先级掩码为0xff，所有中断都可以触发


	
	ICDIPR_CPU(0, 0) = 0;	//设置每个中断的优先级为0。这里设置了4个
	ICDIPR_CPU(1, 0) = 0;
	ICDIPR_CPU(2, 0) = 0;
	ICDIPR_CPU(3, 0) = 0;
	
	ICDIPR_CPU(0, 1) = 0;	//设置每个中断的优先级为0。这里设置了4个
	ICDIPR_CPU(1, 1) = 0;	//设置每个中断的优先级为0。这里设置了4个
	ICDIPR_CPU(2, 1) = 0;	//设置每个中断的优先级为0。这里设置了4个
	ICDIPR_CPU(3, 1) = 0;	//设置每个中断的优先级为0。这里设置了4个
	// 设置哪个CPU来接受中断
	ICDIPTR_CPU(0, 0) = 0x03030303; //0101010101 表示ID为0-4的SGI发送给CPU0,这里的第二个参数是发送者CPU
	ICDIPTR_CPU(0, 1) = 0x03030303;

	set_ICCBPR(0);	//我们不抢占

	// 发送SIG信号
	// bit [25:24] 00表示发送给本寄存器[23:16]号CPU接口， 01表示发送给
	// 除了请求这个中断的CPU外的其他CPU， 10表示只发送给请求的CPU
	// bit[23:16] 发送给的CPU 接口list
	// bit [15]:0表示安全的CPU接口，1表示非安全的CPU接口
	// bit[3:0] 表示此次要发送的CIG号
	ICDSGIR = (3<<16) | (0<<15) | 2; //发送1号GIC给0号CPU接口

}



void gpio_irq_test(void)
{
//	debug("test gic\n");
	open_ICCICR(); //使能中断	
	// 64号中断
	ICDISER_CPU(2, 0) = 0x00000001; //在CPU0上使能64号中断

	open_ICDDCR();	//允许所有外设中断
	
	set_ICCPMR();	// 设置中断优先级掩码为0xff，所有中断都可以触发

	
//	ICDIPR_CPU(0, 0) = 0;	//设置每个中断的优先级为0。这里设置了4个

	// 设置哪个CPU来接受中断
	ICDIPTR_CPU(16, 0) = 0x01; //0101010101 表示ID为0-4的SGI发送给CPU0,这里的第二个参数是发送者CPU

	set_ICCBPR(0);	//我们不抢占

	GPX3CON = (0xF << 8) | (0xF<<12) | (0xF<<16) | (0xF<<20);
	EXT_INT43CON = (2 << 8) | (2 << 12)  | (2 << 16) | (2 <<20);
	EXT_INT43_FLTCON0 = (1<<23) | (1<<31);
	EXT_INT43_FLTCON1 =	 (1<<7) | (1<<15);
	EXT_INT43_MASK = 0;
	EXT_INT43_PEND = 0xFF; //这个可清除，也可以查询
}


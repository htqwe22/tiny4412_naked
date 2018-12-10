
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


#define GIC_BASE		0x10480000

/*
 * CPU interface control register
 * CPU 使能后，相应的CPU可以接受中断
 */
#define ICCICR_CPU(n)	VA(((n)<<14) + GIC_BASE)

/*
 * 优先级掩码(0~0xff),当相应的中断优先级大于这个优先级阀值时，中断才会送到
 * 处理器。优先级越大，值越小。
*/
#define ICCPMR_CPU(n)	VA(((n)<<14) + GIC_BASE + 4)

/*
 * 关于中断分组的。组中断和子中断。组中断决定了优先级
 * 如果值为0，表示前7位是组。如果为7，所有的都是子中断，TABLE 9-6
 */
#define ICCBPR_CPU(n)	VA(((n)<<14) + GIC_BASE + 8)

/* 只读取，用于查询某个CPU正在响应的中断
 * SGI还可以查到是谁发起的SGI
 */
#define ICCIAR_CPU(n)	VA(((n)<<14) + GIC_BASE + 0XC)

/*End of interrupt register
 *只写，清除中断用的
 */
#define ICCEOIR_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X10)


/*
 * 查询某个CPU上正在执行的中断的优先级
 */
#define ICCRPR_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X14)

/*
 * 查询最高的pending中断只对SGI有效
 * 还可以查询到是谁发的，哪个SIG ID
 */
#define ICCHPIR_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X18)

/*
 * 非安全的ICCBPR的别名，只有在实现了安全扩展的基础上有用
 */
#define ICCABPR_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X1C)

/*
 * 中断测试接口， 它不会产生CPU 接口的输出信号
 */
#define  INTEG_EN_C_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X40)

/*
 * 可以设置和读取每个CPU接口的irq的状态，高还是低
 */
#define  INTERRUPT_OUT_CPU(n)	VA(((n)<<14) + GIC_BASE + 0X44)

/*
 * GIC的标识ID
 */
#define ICCIIDR			VA(GIC_BASE + 0XFC)



#define DISTRIBUTOR_BASE	0x10490000
/*
 * 是否允许外设中断到CPU接口
 */
#define ICDDCR				VA(DISTRIBUTOR_BASE)

/*
 * 只读的：就是表示当前GIC实现了哪些功能
 */
#define ICDICTR				VA(DISTRIBUTOR_BASE + 4)

/*
 * 只读：分配器版本号相关
 */
#define ICDIIDR				VA(DISTRIBUTOR_BASE + 8)


/*
 * 对每个中断在不同的CPU上的安全扩展状态的设置和读取
 */
#define ICDISR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x80)

/*
 * 每个中断在不同CPU上的设置使能
 */
#define ICDISER_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0100)

/*
 * 每个中断在不同CPU上的清除使能
 */
#define ICDICER_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0180)

/*
 * 设置每个中断在不同CPU上pending状态设置
 */
#define ICDISPR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0200)


/*
 * 清除每个中断在不同CPU上pending状态设置
 */
#define ICDICPR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0280)


/*
 * 设置或查询每个中断的激活状态
 */
#define ICDABR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0300)


/*
 * 设置或查询每个中断的8位优先级。表9-13
 */
#define ICDIPR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0400)


/*
 * 设置或查询每个中断对应的处理CPUs 接口。每8bit表示一个中断，表9-10
 * 按掩码的方式来表示。比如3，表示这个中断会要0和1号CPU 接口来处理。
 */
#define ICDIPTR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0800)


/*
 * 读取每个中断的触发方式
 */
#define ICDICFR_CPU(i, n)	VA(((n)<<14) + ((i)<<2) + DISTRIBUTOR_BASE + 0x0C00)

/*
 * 只有在安全中断下才能使用
 * 读取PPIn在每个分配器上的状态（PPI是与每个CPU接口相关的）
 */
#define PPI_STATUS_CPU(n)	VA(((n)<<14) +  DISTRIBUTOR_BASE + 0xD00)




/*
 * 只有在安全中断下才能使用
 * 读取SPI在每个分配器上的状态
 */
#define SPI_STATUS(n)	VA(((n)<<2) +  DISTRIBUTOR_BASE + 0xD04)

/*
 * 用于发送SGI中断的
 */
#define ICDSGIR				VA(DISTRIBUTOR_BASE + 0x0F00)


#define GPX3CON (*(volatile unsigned int *)0x11000c60)
#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

#define EXT_INT43CON		VA(0x11000000 + 0x0E0C)
#define EXT_INT43_FLTCON0	VA(0x11000000 + 0x0E98)
#define EXT_INT43_FLTCON1	VA(0x11000000 + 0x0E9C)
#define EXT_INT43_MASK		VA(0x11000000 + 0x0F0C)
#define EXT_INT43_PEND		VA(0x11000000 + 0x0F4C)


unsigned long get_sp();

void show_current_sp(unsigned long sp, unsigned long lr);

void exception_undefined_instruction(unsigned long lr);

void exception_software_interrupt(unsigned long lr, unsigned long index);
	
void exception_prefetch_abort(unsigned long lr);

void exception_data_abort(unsigned long lr);

void exception_irq(unsigned long lr);

void exception_fiq(unsigned long lr);


void enable_irq_fiq(void);


#ifdef __cplusplus
}
#endif

#endif

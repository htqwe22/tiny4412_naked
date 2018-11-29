
/**********************************************************************************
 * FILE : mmu.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-11-25 , At 03:18:11
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "mmu.h"
#include "util.h"

#define BASE_PAGE_ADDR	0x02020000

/* 一级描述符bit[1:0] = 0b10 为段描述
* ----------------------------------------------------------------
* |31 ... 20 | 19 ... 12 | 11 10(AP) | 9 |8 .. 5 (domain)|4 |3(C) |2(B)| 1 | 0 |
* ----------------------------------------------------------------
* | base	 | 0(fix)	  | 0	     |0  | 0 domain	     |1 |  0  |	0  | 1 |0  |
* ----------------------------------------------------------------	 
*/

#define make_base_entry(base, ap, d, c, b) \
	((base)<<20) |((ap)<<10) | ((d)<<5) | (1 << 4) | ((c)<<3) | ((b)<<2) | (2)

uint32_t *get_base_page_addr(void)
{
	return (uint32_t*) ((BASE_PAGE_ADDR>>14) << 14); //16 align
}

/*
 * 我的想法是把0地址映射到40000000， 这样的话，中断就可以用了
 * 40000000也映射到这个地址是为了在开启MMU的时候指令不会跑飞。
 */
void init_base_page(void)
{
	uint32_t index;
	uint32_t *base_page_addr = get_base_page_addr();
	//第0号表
	index = 0;
	base_page_addr[0] = make_base_entry(0x400, 3, 0, 0, 0);
	for (index = 1; index < 0x200; index++)	//平行映射
		base_page_addr[index] = make_base_entry(index, 3, 0, 0, 0);
	
	for (index = 0x200; index < 0x400; index++)
		base_page_addr[index] = 0;  //虚拟地址从0x200xxxxx到0x3fffffff的不能使用

	for (index = 0x400; index < 0x800; index++)	// 1G的空间
		base_page_addr[index] = make_base_entry(index, 3, 0, 1, 1);
	
	for (index = 0x800; index < 0xc00; index++)
			base_page_addr[index] = 0;	//虚拟地址从0x800xxxxx到0xBfffffff的不能使用

	for (index = 0xC00; index <= 0xFFF; index++)	// 1G的空间
		base_page_addr[index] = make_base_entry(index-0x8000, 3, 0, 1, 1);

}

void enable_mmu(void)
{
	asm("ldr	r5, =0x0000ffff\n"
		"mcr	p15, 0, r5, c3, c0, 0\n"
		"ldr	r1, =0x02020000\n"
		"mcr	p15, 0, r1, c2, c0, 0\n"
		
		"mrc	p15, 0, r0, c1, c0, 0\n"
		"orr	r0, r0, #1\n"
		"mcr	p15, 0, r0, c1, c0, 0\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
	);
}


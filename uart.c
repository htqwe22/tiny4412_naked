#include "console.h"

#define USE_24M

#ifndef NULL 
#define NULL ((void *)0) 
#endif

#define VA(addr)  (*(volatile unsigned int *)(addr))

#define UART0_BASE 	0x13800000
#define ULCON 		UART0_BASE + 0
#define UCON 		UART0_BASE + 4
#define UFCON 		UART0_BASE + 8
#define UMCON  		UART0_BASE + 0xc
#define UTRSTAT 	UART0_BASE + 0X10
#define UERSTAT  	UART0_BASE + 0x14
#define UFSTAT 		UART0_BASE + 0x18
#define UMSTAT  	UART0_BASE + 0x1c
#define UTXH 		UART0_BASE + 0x20
#define URXH 		UART0_BASE + 0x24
#define UBRDIV 		UART0_BASE + 0x28
#define UFRACVAL 	UART0_BASE + 0x2c
#define UINTP 		UART0_BASE + 0x30
#define UINTSP 		UART0_BASE + 0x34
#define UINTM 		UART0_BASE + 0x38

#define GPA0CON		0x11400000

// system clock
#define CLK_SRC_PERIL0 0x1003C250
#define CLK_DIV_PERIL0 0x1003C550


void uart_init(int baudrate)
{
	unsigned int tmp;
	tmp = VA(GPA0CON);
	tmp &= ~0xff;
	tmp |= 0x22;
	VA(GPA0CON) = tmp;
#ifdef USE_24M
	//VA(CLK_SRC_PERIL0) = 0;//(6<<16) | (6<<12) | (6<<8) | (6<<4) | 6;
	//VA(CLK_DIV_PERIL0) = 0x11111;//(7<<20) | (7<<16) | (7<<8) | (7<<4) | 7;
	VA(CLK_SRC_PERIL0) = (1<<16) | (1<<12) | (1<<8) | (1<<4) | 1;
	VA(CLK_DIV_PERIL0) = 0; //(7<<20) | (7<<16) | (7<<8) | (7<<4) | 7;
#else	
	(0<<24) | (6<<20) |  (6 << 16) | (6<<12) | (6<<8) | (6<<4) | 6;
	VA(CLK_SRC_PERIL0) = (6<<16) | (6<<12) | (6<<8) | (6<<4) | 6;
	(7<<20) |  (7 << 16) | (7<<12) | (8<<8) | (8<<4) | 68;
	VA(CLK_DIV_PERIL0) = (7<<20) | (7<<16) | (7<<8) | (7<<4) | 7;
#endif	
	VA(UFCON) = 0x011;
	VA(ULCON) = 3;
	VA(UCON) = 5;

#ifdef USE_24M
	VA(UBRDIV) = 12;//0x35;
	VA(UFRACVAL) = 0;//4;
#else
	VA(UBRDIV) = 0x35;
	VA(UFRACVAL) = 4;
#endif

}


int fputc(int ch, FILE*f)
{
	VA(UTXH) = ch;
	while ((VA(UTRSTAT) &(3 <<1) == 0 ));
	return ch;
}

int fgetc(FILE *f) 
{
	if (VA(UTRSTAT) & 1)
		return VA(URXH);
	return -1;
}	



#if 0
int puts(const char *s)
{
	if (s == NULL)
		return;
	while (*s) 
		putc(*s++);
	return 1;
}
#endif

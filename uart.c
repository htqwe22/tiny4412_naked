#include "console.h"
#include "ring_fifo.h"
#include "exception.h"
#define USE_24M

#ifndef NULL 
#define NULL ((void *)0) 
#endif

static struct ring_fifo uart_rx_fifo;
uint8_t fifo_buffer[512];

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

void uart_irq_handler(void)
{
	uint32_t tmp, fstat;
	uint16_t recvbyts;
	uint8_t ch;
	
	tmp = VA(UINTP);
	if (tmp & 4) //TX
	{
		VA(UINTM) |= 4; // disable
	}
	if (tmp & 1)
	{
		fstat = VA(UFSTAT);
		recvbyts = fstat & 0xff;
		if (fstat & (0x100))
			recvbyts = 0xff;
		while(recvbyts)
		{
			ch = VA(URXH);
			ring_fifo_put_one(&uart_rx_fifo, &ch);
			recvbyts--;
		}
		if (VA(UTRSTAT) & 8)
			VA(UTRSTAT) |= 8;
	}
	VA(UINTP) = tmp;
}

void uart_init(int baudrate)
{
	ring_fifo_init(&uart_rx_fifo, fifo_buffer, sizeof(fifo_buffer), 1);
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
	VA(UFCON) = 0x017; // fifo mode 64 bytes triggle level
	VA(ULCON) = 3;
	VA(UCON) = 5 | (1<<7) | (1<<9); // timeout receive
	VA(UINTM) = 0x0E; //disable
#ifdef USE_24M
	VA(UBRDIV) = 12;//0x35;
	VA(UFRACVAL) = 0;//4;
#else
	VA(UBRDIV) = 0x35;
	VA(UFRACVAL) = 4;
#endif
	enable_gic_irq_id(84);
}


int fputc(int ch, FILE*f)
{
	VA(UTXH) = ch;
	while ((VA(UTRSTAT) &(3 <<1) == 0 ));
	return ch;
}

int fgetc(FILE *f) 
{
	uint8_t ch;
#if 0
	if (VA(UTRSTAT) & 1)
		return VA(URXH);
	return -1;
#else
	if (1 == ring_fifo_get_one(&uart_rx_fifo,&ch))
		return ch;
	return -1;
#endif
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

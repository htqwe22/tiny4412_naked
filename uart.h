#ifndef KV_UART__H
#define KV_UART__H



void uart_init(int baudrate);


void putc(const char c);


int getc(void);


void puts(const char *s);




#endif


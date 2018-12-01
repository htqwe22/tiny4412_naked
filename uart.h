#ifndef KV_UART__H
#define KV_UART__H



void uart_init(int baudrate);


void kv_putc(const char c);


int kv_getc(void);


void kv_puts(const char *s);




#endif


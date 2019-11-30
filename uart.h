#ifndef KV_UART__H
#define KV_UART__H

void uart_init(int baudrate);


int uart_send_use_fifo(const void *data, int len);

int uart_print_tx_fifo(int len);


#endif


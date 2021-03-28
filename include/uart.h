#ifndef UART_H
#define UART_H

// Control functions
void uart_init();
void uart_enable();
void uart_disable();

unsigned char uart_getc();
void uart_putc(unsigned char c);
void uart_puts(const char* str);

#endif

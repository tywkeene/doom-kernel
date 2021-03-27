#ifndef PRINTK_H
#define PRINTK_H

#include <stdint.h>
#include <sys/types.h>
#include <stdarg.h>

void putch(uint16_t, char);
void putstr(uint16_t, const char *);
void putoct(uint16_t, uint32_t, uint16_t, uint8_t);
void putdec(uint16_t, int, uint16_t, uint8_t);
void puthex(uint16_t, uint32_t, uint16_t, uint8_t);
void putuns(uint16_t, uint32_t, uint16_t, uint8_t);
void vaprintk(uint16_t, char *, va_list);
void printk(char *, ...);

#endif

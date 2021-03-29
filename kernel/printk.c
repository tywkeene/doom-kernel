#include <stddef.h>
#include <stdint.h>

#include "../include/uart.h"

#define abs(x) __builtin_abs(x)

#ifndef _STDARG_SYS_
#define _STDARG_SYS_
#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;
#endif

void putch(char c) {
	uart_putc(c);
}

void putstr(const char *str) {
	while(*str){
		putch( *str);
		str++;
	}
	return;
}

void putoct(uint32_t val, uint16_t width, uint8_t zeropad) {
	if(!width){
		char c[11];
		uint32_t i = 0;
		do {
			c[i++] ='0'+(val&0x07);
			val >>= 3;
		}
		while(val != 0);
		while(i > 0)
			putch(c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] ='0'+(val&0x07);
			val >>= 3;
		}
		while((val != 0) && (i < width));
		while(i < width)
			c[i++] = (zeropad)?'0':' ';
		while ( i > 0 )
			putch(c[--i]);
	}
	return;
}

void putdec(int val, uint16_t width, uint8_t zeropad) {
	uint8_t isneg = (val < 0);
	val = abs(val);
	if(!width) {
		char c[10];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( val != 0 );
		if ( isneg )
			putch('-');
		while ( i > 0 )
			putch(c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( (val != 0) && (i < width) );
		if(isneg)
			putch('-');
		while(i < width)
			c[i++] = (zeropad)?'0':' ';
		while(i > 0)
			putch(c[--i]);
	}
}

void puthex(uint32_t val, uint16_t width, uint8_t zeropad ) {
	if(!width){
		char c[8];
		uint32_t i = 0;
		do{
			c[i++] = ((val&0x0F)>0x09)?('A'+(val&0x0F)-0x0A)
				:('0'+(val&0x0F));
			val >>= 4;
		}
		while(val != 0);
		while(i > 0)
			putch(c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = ((val&0x0F)>0x09)?('A'+(val&0x0F)-0x0A)
				:('0'+(val&0x0F));
			val >>= 4;
		}
		while((val != 0) && (i < width));
		while(i < width)
			c[i++] = (zeropad)?'0':' ';
		while(i > 0)
			putch(c[--i]);
	}
}

void putuns(uint32_t val, uint16_t width, uint8_t zeropad )
{
	if(!width){
		char c[10];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while(val != 0);
		while(i > 0)
			putch(c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while((val != 0) && (i < width));
		while(i < width)
			c[i++] = (zeropad)?'0':' ';
		while(i > 0)
			putch(c[--i]);
	}
}

void vaprintk(char *s, va_list args )
{
	uint8_t alt;
	uint8_t zp;
	uint16_t wide;
	int i;

	for(i = 0; s[i] != 0x00; i++)
		;

	while ( *s ){
		alt = 0;
		zp = 0;
		wide = 0;

		if(*s != '%'){
			putch(*(s++));
			continue;
		}
		s++;
		if(*s == '%'){
			putch(*(s++));
			continue;
		}
		if(*s == 's'){
			putstr((char*)va_arg(args, char *));
			s++;
			continue;
		}
		if(*s == 'c'){
			putch(va_arg(args, int));
			s++;
			continue;
		}
		if(*s == '#'){
			alt = 1;
			s++;
		}
		if(*s == '0'){
			zp = 1;
			s++;
		}
		while ( (*s >= '0') && (*s <= '9') ) /* field width */
			wide = wide*10+(*(s++)-'0');
		if(*s == 'd'){
			putdec((uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'u'){
			putuns((uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'x'){
			if(alt)
				putstr("0x");
			puthex((uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'o' ){
			if(alt)
				putch('0');
			putoct((uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		putch(*(s++));
	}
}

void printk(char *str, ...)
{
	va_list args;
	va_start(args, str);
	vaprintk(str, args);
	va_end(args);
	return;
} 

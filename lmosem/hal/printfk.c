/*********************
 * printfk.c 2016.01.11
 * ******************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

spinlock_t print_lock;

void print_init()
{
    hal_spinlock_init(&print_lock);
    return;
}

uint_t g_i_2;

void printfk_new(const char_t * fmt, ...)
{
//hal_spinlock_lock(&print_lock);
//hal_disable_irq();
    cpuflg_t cpuflg;
    hal_disableirq_savecpuflg(&cpuflg);
    g_i_2 = 10;
    char_t buf_print[512];
    va_list ap;
    g_i_2 = 20;
    va_start(ap, fmt);
    g_i_2 = 30;
    //hal_memset(buf_print, 512, 0);
    g_i_2 = 40;
    vsprintfk(buf_print, fmt, ap);
    g_i_2 = 50;
    //hal_uart_write(0, buf_print, 0);
    g_i_2 = 60;
    va_end(ap);
    g_i_2 = 90;
    hal_enableirq_restcpuflg(&cpuflg);
    g_i_2 = 100;
//hal_enable_irq();
//hal_spinlock_unlock(&print_lock);
    return;
}


void printfk(const char_t * fmt, ...)
{
//    hal_spinlock_lock(&print_lock);
    //hal_disable_irq();
    cpuflg_t cpuflg;
    hal_disableirq_savecpuflg(&cpuflg);
    char_t buf_print[512];
    va_list ap;
    va_start(ap, fmt);
    //hal_memset(buf_print, 512, 0);
    vsprintfk(buf_print, fmt, ap);
    hal_uart_write(0, buf_print, 0);
    va_end(ap);
    hal_enableirq_restcpuflg(&cpuflg);
    //hal_enable_irq();
  //  hal_spinlock_unlock(&print_lock);
    return;
}

char_t * strcopyk(char_t * buf, char_t * str_s)
{
    while(*str_s)
    {
	*buf = *str_s;
	buf++;
	str_s++;
    }
    return buf;
}

void vsprintfk(char_t * buf, const char_t * fmt, va_list args)
{
    char_t * p = buf;
    va_list next_arg = args;
    while(*fmt)
    {
	if(*fmt != '%')
	{
	    *p++ = *fmt++;
	    continue;
	}
	fmt++;
	switch(*fmt)
	{
	    case 'x':
		p = numberk(p, va_arg(next_arg, uint_t), 16);
		fmt++;
		break;
	    case 'd':
		p = numberk(p, va_arg(next_arg, uint_t), 10);
		fmt++;
		break;
	    case 's':
		p = strcopyk(p, (char_t*)va_arg(next_arg, uint_t));
		fmt++;
		break;
	    default:
		break;
	}
    }
    *p = 0;
    return;
}

char_t * numberk(char_t *str, uint_t n, sint_t base)
{
    register char_t *p;
    char_t strbuf[36];
    p = &strbuf[36];
    *--p = 0;
    if(n == 0)
    {
	*--p = '0';
    }
    else
    {
	do
	{
	    *--p = "0123456789abcdef"[n % base];
	}while(n /= base);
    }

    while(*p != 0)
    {
	*str++ = *p++;
    }
    return str;
}

void char_write_uart(char_t * buf)
{
    char_t *p = buf;
    while(*p)
    {
//	hal_uart0_putc(*p);
	p++;
    }
    return;
}

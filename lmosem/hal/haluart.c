/*************************
 * haluart.c 2016.01.24
 * **********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void hello_word(void)
{
    printfk("\n\r");
    printfk("/******************Lmosem***********************/\n\r");
    printfk("/**********Hello, I miss you so much************/\n\r");
}

extern void print_init();

void init_haluart()
{
    init_uart0();
    print_init();
    hello_word();  
    uint_t vall = 25;
    char_t * str = "/***test*****/";
    printfk("test print %s, vald is %d, valx is 0x%x\n\r", str, vall, vall);
    return;
}

void init_uart0()
{
    hal_io32_write(ULCON0_R,3);
    hal_io32_write(UCON0_R,5);
    hal_io32_write(UFCON0_R,0);
    hal_io32_write(UMCON0_R,0);
    hal_io32_write(UBRDIV0_R,26);
    return;
}

void hal_uart0_putc(char_t c)
{
    while(!(hal_io32_read(UTRSTAT0_R)&4));

    hal_io32_write(UTXH0_R, c);
    return;
}

drvstus_t hal_uart_write(uint_t uart, void * buf, uint_t len)
{
    char_t * p = buf;
    cpuflg_t cpuflg;
    hal_disableirq_savecpuflg(&cpuflg);

    while(*p)
    {
	if(uart_send_char(uart, *p) == DFCERRSTUS)
	{
	    hal_sysdie("uart err");
	    return DFCERRSTUS;
	}
	p++;
    }

    hal_enableirq_restcpuflg(&cpuflg);
    return DFCOKSTUS;
}

drvstus_t hal_uart_read(uint_t uart, void * buf, uint_t *retlen)
{
    return DFCOKSTUS;
}

drvstus_t hal_uart_ioctrl(uint_t uart, uint_t ctrlcode, void * ctrdata)
{
    return DFCOKSTUS;
}

drvstus_t uart_send_char(uint_t uart, char_t ch)
{
    uint_t time = 0;
    if(uart != 0)
    {
	return DFCERRSTUS;
    }

    while(!(hal_io32_read(UTRSTAT0_R)&4))
    {
	if(time>0x100000)
	{
	    return DFCERRSTUS;
	}
	time++;
    }
    hal_io32_write(UTXH0_R,ch);

    return DFCOKSTUS;
}

drvstus_t uart_receive_char(uint_t uart, char_t * retch)
{
    return DFCOKSTUS;
}

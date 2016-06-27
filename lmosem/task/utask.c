/********************
 * utask.c 2016.05.13
 * *****************/
#include "stdio.h"
//#include "lmosemtypes.h"
//#include "lmosemmctrl.h"
/*
void usr_write_file()
{
    char * buf = (char *)mallocblk(0x1000);
    if(buf == NULL)
    {
	goto err;
    }

    for(int i=0; i<512; i++)
    {
	buf[i] = 0xFF;
    }

    if(open("/file.bin", NF_FLG | FILE_TY_FILE, 0) == -1)
    {
	goto err;
    }

    hand_t fd = open("/file.bin", RW_FLG | FILE_TY_FILE, 0);
    if(fd == -1)
    {
	goto err;
    }

    if(write(fd, buf, 512, 0) == SYSSTUSERR)
    {
	goto err;
    }

    close(fd);

    if(mfreeblk(buf, 0x1000) == SYSSTUSERR)
    {
	goto err;
    }

    return;

err:
    printf("uar_write_file err\n\r");
    while(1);
    return;
}

void usr_read_file()
{

    char* buf=(char*)mallocblk(0x1000);
    if(buf==NULL)
    {
        goto err;
    }
    for(int i=0;i<0x1000;i++)
    {
        buf[i]=0;
    }

    hand_t fd=open("/file.bin",RW_FLG|FILE_TY_FILE,0);
    if(fd==-1)
    {
        goto err;
    }
    if(read(fd,buf,512,0)==SYSSTUSERR)
    {
        goto err;
    }
    for(int j=0;j<512;j++)
    {
        if(buf[j]!=0xff)
        {
            goto err;
        }
    }
    close(fd);
    if(mfreeblk(buf,0x1000)==SYSSTUSERR)
    {
        goto err;
    }
    return;
err:
    printf("usr_read_file err\n\r");
    for(;;);
    return;
}
*/
uint_t g_i_1 = 0;
uint_t g_i_0 = 0;
void task1_main()
{
    int i = 0;
    for(;;)
    {
	i++;
	g_i_1++;
	//printfk("task1 run %d, %d\n\r", i, g_i_1);
	printf("task1 run %d, %d\n\r", i, g_i_1);
    }
    return;
}

void task0_main()
{
    int i = 0;
    for(;;)
    {
	i++;
	g_i_0++;
	//printfk("task0 run %d ,%d\n\r", i, g_i_0);
	printf("task0 run %d ,%d\n\r", i, g_i_0);
    }
}

void task2_main()
{
    int i = 0;
    times_t timet;

    //usr_write_file();
    //usr_read_file();

    for(;;)
    {
	i++;
	printf("task1 run %x task1ID:%x\n\r", i, pid(NULL));
	time(&timet);
	printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r", \
		timet.year, timet.mon, timet.date, timet.hour, timet.min, timet.sec);
    }

    return;
}

void task3_main()
{
    times_t timet;
    int i=0;
    for(;;)
    {
	i++;
	printf("task3 run %x task3ID:%x \n\r",i,pid(NULL));
	gettime(&timet);
	printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",
	 timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
    }
    return;
}

void task4_main()
{
    times_t timet;
    timet.year = 14;
    timet.mon = 9;
    timet.day = 4;
    timet.date = 11;
    timet.hour = 12;
    timet.min = 30;
    timet.sec = 00;

    settime(&timet);

    int i = 0;
    for(;;)
    {
	i++;
	g_i_0++;
	printf("task4 run %x task4ID:%x \n\r",i,pid(NULL));
	gettime(&timet);
	printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",
	 timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
    }
    return;
}

void task5_main()
{
    int i=0;
    for(;;)
    {
	i++;
	g_i_1++;
	printf("task5 run \n\r");
	//printf("task5 run %x task5ID:%x \n\r", i, pid(NULL));
    }
    return;
}

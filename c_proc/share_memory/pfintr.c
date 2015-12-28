#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME    "/proc/stat"
#define DEFAULTTIME 5

static void sig_handler(int signo);
int get_page_fault(void);
int readfile(char *data);
int exit_flag = 0;
int page_fault;

int main(int argc, char **argv)
{
    struct itimerval v;
    int calc_time;

    if(signal(SIGALRM, sig_handler) == SIG_ERR) {
	printf("Unable to create handler for SIGALRM\n");
	return -1;
    }

    if(argc <=2)
	page_fault = get_page_fault();

    if(argc < 2) {
	printf("Use default time!\n");
	calc_time = DEFAULTTIME;
    }
    else if(argc == 2) {
	printf("Use user's time\n");
	calc_time = atoi(argv[1]);
    }
    else {
	printf("Usage:mypage [time]\n");
	return 0;
    }

    v.it_interval.tv_sec = calc_time;
    v.it_interval.tv_usec = 0;
    v.it_value.tv_sec = calc_time;
    v.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &v, NULL);

    while(!exit_flag);

    printf("In %d seconds, system calls %d page fault!\n",calc_time, page_fault);

    return 0;
}

static void sig_handler(int signo)
{
    if(signo == SIGALRM) {
	page_fault = page_fault - get_page_fault();
	exit_flag = 1;
    }
}

int get_page_fault(void)
{
    char d[50];
    int retval;

    retval = readfile(d);
    if(retval < 0) {
	printf("read data from file failed\n");
	exit(0);
    }
    printf("Now the number of page fault is %s\n",d);
    return atoi(d);
}

int readfile(char *data)
{
    int fd;
    int seekcount = 0;
    int retval = 0;
    int i = 0;
    int count = 0;
    char c, string[50];

    fd = open(FILENAME, O_RDONLY);
    if(fd < 0) {
	printf("Open file /proc/stat failed\n");
	return -1;
    }

    do{
	i = 0;
	do {
	    lseek(fd, seekcount, SEEK_SET);
	    retval = read(fd, &c, sizeof(char));
	    if (retval < 0) {
		printf("read file error!\n");
		return retval;
	    }
	    seekcount += sizeof(char);

	    if(c == ' ' || c == '\n') {
		string[i] = 0;
		break;
	    }
	    if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		string[i++] = c;
	    }
	}while(1);
    }while(strcmp("intr", string));

    printf("find intr!\n");

    do {
	lseek(fd, seekcount, SEEK_SET);
	retval = read(fd, &c, sizeof(char));
	if (retval < 0) {
	    printf("read file error!\n");
	    return retval;
	}

	seekcount += sizeof(char);
	if (c == ' ' || c == '\n') {
	    string[i] = 0;
	    i = 0;
	    count++;
	}
	if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
	    string[i++] = c;
	}
    }while(count != 16);

    close(fd);
    strcpy(data, string);
    return 0;
}

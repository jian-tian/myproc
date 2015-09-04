#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

long unsigned int fibonacci(unsigned int n);
static void par_sig(int signo);
static void c1_sig(int signo);
static void c2_sig(int signo);

static long p_realt_secs = 0, c1_realt_secs = 0, c2_realt_secs = 0;
static long p_virtt_secs = 0, c1_virtt_secs = 0, c2_virtt_secs = 0;
static long p_proftt_secs = 0, c1_proftt_secs = 0, c2_proftt_secs = 0;
static struct itimerval p_realt, c1_realt, c2_realt; 
static struct itimerval p_virtt, c1_virtt, c2_virtt; 
static struct itimerval p_proftt, c1_proftt, c2_proftt; 

int main()
{

    long unsigned lib = 0;
    int pid1,pid2;
    unsigned int fibarg = 39;
    int status;
    struct itimerval v;
    long moresec,moremsec,t1,t2;

    pid1 = fork();
    if (pid1 == 0) {
	signal(SIGALRM, c1_sig);
	signal(SIGVTALRM, c1_sig);
	signal(SIGPROF, c1_sig);
	v.it_interval.tv_sec = 10;
	v.it_interval.tv_usec = 0;
	v.it_value.tv_sec = 10;
	v.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &v, NULL);
	setitimer(ITIMER_VIRTUAL, &v, NULL);
	setitimer(ITIMER_PROF, &v, NULL);
	fib = fibonacci(fibarg);
	getitimer(ITIMER_REAL, &c1_proft);
	getitimer(ITIMER_VIRTUAL, &c1_realt);
	getitimer(ITIMER_PROF, &c1_virtt);
	
	moresec = 9 - c1_realt.it_value.tv_sec;
	moremsec = (1000000 - c1_realt.it_value.tv_usec)/1000;
	printf("Child1 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c1_realt_secs + moresec, moremsec);

	moresec = 9 - c1_proft.it_value.tv_sec;
	moremsec = (1000000 - c1_proft.it_value.tv_usec)/1000;
	printf("Child1 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c1_proft_secs + moresec, moremsec);

	moresec = 9 - c1_proft.it_value.tv_sec;
	moremsec = (1000000 - c1_proft.it_value.tv_usec)/1000;
	printf("Child1 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c1_proft_secs + moresec, moremsec);

	t1 = (9 - c1_proft.it_value.tv_sec) * 1000 + (1000000 - c1_proft.it_value.tv_usec)/1000 + c1_proft_secs*10000;
	t2 = (9 - c1_virtt.it_value.tv_sec) * 1000 + (1000000 - c1_virtt.it_value.tv_usec)/1000 + c1_virtt_secs*10000;

	moresec = (t1 - t2) / 1000;
	moremsec = (t1 - t2) % 1000;
	printf("Child1 fib=%ld, kernel_time=%ld sec,%ld msec\n", fib, moresec, moremsec);
	
	fflush(stdout);
	exit(0);
    }
    else {
	pid2 = fork();
	if (pid2 == 0) {
	    signal(SIGALRM, c2_sig);
	    signal(SIGVTALRM, c2_sig);
	    signal(SIGPROF, c2_sig);
	    v.it_interval.tv_sec = 10;
	    v.it_interval.tv_usec = 0;
	    v.it_value.tv_sec = 10;
	    v.it_value.tv_usec = 0;
	    setitimer(ITIMER_REAL, &v, NULL);
	    setitimer(ITIMER_VIRTUAL, &v, NULL);
	    setitimer(ITIMER_PROF, &v, NULL);
	    fib = fibonacci(fibarg);
	    getitimer(ITIMER_REAL, &c2_proft);
	    getitimer(ITIMER_VIRTUAL, &c2_realt);
	    getitimer(ITIMER_PROF, &c2_virtt);
	
	    moresec = 9 - c2_realt.it_value.tv_sec;
	    moremsec = (1000000 - c2_realt.it_value.tv_usec)/1000;
	    printf("Child2 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c2_realt_secs + moresec, moremsec);

	    moresec = 9 - c2_proft.it_value.tv_sec;
	    moremsec = (1000000 - c2_proft.it_value.tv_usec)/1000;
	    printf("Child1 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c2_proft_secs + moresec, moremsec);

	    moresec = 9 - c2_proft.it_value.tv_sec;
	    moremsec = (1000000 - c2_proft.it_value.tv_usec)/1000;
	    printf("Child2 fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, c2_proft_secs + moresec, moremsec);

	    t1 = (9 - c2_proft.it_value.tv_sec) * 1000 + (1000000 - c2_proft.it_value.tv_usec)/1000 + c1_proft_secs*10000;
	    t2 = (9 - c2_virtt.it_value.tv_sec) * 1000 + (1000000 - c2_virtt.it_value.tv_usec)/1000 + c1_virtt_secs*10000;

	    moresec = (t1 - t2) / 1000;
	    moremsec = (t1 - t2) % 1000;
	    printf("Child2 fib=%ld, kernel_time=%ld sec,%ld msec\n", fib, moresec, moremsec);
	
	    fflush(stdout);
	    exit(0);
	}
	else {
	    signal(SIGALRM, par_sig);
	    signal(SIGVTALRM, par_sig);
	    signal(SIGPROF, par_sig);
	    v.it_interval.tv_sec = 10;
	    v.it_interval.tv_usec = 0;
	    v.it_value.tv_sec = 10;
	    v.it_value.tv_usec = 0;
	    setitimer(ITIMER_REAL, &v, NULL);
	    setitimer(ITIMER_VIRTUAL, &v, NULL);
	    setitimer(ITIMER_PROF, &v, NULL);
	    fib = fibonacci(fibarg);
	    getitimer(ITIMER_REAL, &p_proft);
	    getitimer(ITIMER_VIRTUAL, &p_realt);
	    getitimer(ITIMER_PROF, &p_virtt);
	
	    moresec = 9 - p_realt.it_value.tv_sec;
	    moremsec = (1000000 - p_realt.it_value.tv_usec)/1000;
	    printf("Parent fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, p_realt_secs + moresec, moremsec);

	    moresec = 9 - p_proft.it_value.tv_sec;
	    moremsec = (1000000 - p_proft.it_value.tv_usec)/1000;
	    printf("Parent fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, p_proft_secs + moresec, moremsec);

	    moresec = 9 - p_proft.it_value.tv_sec;
	    moremsec = (1000000 - p_proft.it_value.tv_usec)/1000;
	    printf("Parent fib = %ld, real_time = %ld sec, %ld msec %ld\n", fib, p_proft_secs + moresec, moremsec);

	    t1 = (9 - p_proft.it_value.tv_sec) * 1000 + (1000000 - p_proft.it_value.tv_usec)/1000 + c1_proft_secs*10000;
	    t2 = (9 - p_virtt.it_value.tv_sec) * 1000 + (1000000 - p_virtt.it_value.tv_usec)/1000 + c1_virtt_secs*10000;

	    moresec = (t1 - t2) / 1000;
	    moremsec = (t1 - t2) % 1000;
	    printf("Parent fib=%ld, kernel_time=%ld sec,%ld msec\n", fib, moresec, moremsec);
	
	    fflush(stdout);
	    waitpid(0, &status, 0);
	    waitpid(0, &status, 0);
	    exit(0);
	}
	printf("thi line should never be printed\n");
    }
}

long unsigned fibonacci(unsigned int n)
{
    if (n == 0)
	return 0;
    else if(n == 1 || n ==2)
	return 1;
    else
	return fibonacci(n-1) + fibonacci(n-2);
}

static par_sig(int signo)
{
    switch (signo) {
	case SIGALRM:
	    p_realt_secs += 10;
	    break;
	case SIGVTALRM:
	    p_virtt_secs += 10;
	    break;
	case SIGPROF:
	    p_proftt_secs += 10;
	    break;
    }
}

static c1_sig(int signo)
{
    switch (signo) {
	case SIGALRM:
	    c1_realt_secs += 10;
	    break;
	case SIGVTALRM:
	    c1_virtt_secs += 10;
	    break;
	case SIGPROF:
	    c1_proftt_secs += 10;
	    break;
    }
}

static c2_sig(int signo)
{
    switch (signo) {
	case SIGALRM:
	    c2_realt_secs += 10;
	    break;
	case SIGVTALRM:
	    c2_virtt_secs += 10;
	    break;
	case SIGPROF:
	    c2_proftt_secs += 10;
	    break;
    }
}



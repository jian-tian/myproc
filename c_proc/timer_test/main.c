#include <signal.h>
#include <sys/time.h>
#include <stdio.h>

static void sig_handler(int signo);

long lastsec, countsec;

int main(void)
{
    struct itimerval v;
    long nowsec,nowusec;

    if(signal(SIGUSR1, sig_handler) == SIG_ERR) {
	printf("Unable to create handler for SIGUSR1\n");
	exit(0);
    }

    if(signal(SIGALRM, sig_handler) == SIG_ERR) {
	printf("Unable to create handler for SIGALRM\n");
	exit(0);
    }

    v.it_interval.tv_sec = 9;
    v.it_interval.tv_usec = 999999;
    v.it_value.tv_sec = 9;
    v.it_value.tv_usec = 999999;

    setitimer(ITIMER_REAL, &v, NULL);
    setitimer(ITIMER_VIRTUAL, &v, NULL);
    setitimer(ITIMER_PROF, &v, NULL);

    lastsec = v.it_value.tv_sec;
    countsec = 0;

    while(1) {
	getitimer(ITIMER_REAL, &v);
	nowsec = v.it_value.tv_sec;
	nowusec = v.it_value.tv_usec;
	if (nowsec == lastsec - 1) {
	    if (nowsec < 9){
		raise(SIGUSR1);
		lastsec = nowsec;
	    }
	    countsec++;
	}
    }
}

static void sig_handler(int signo)
{
    struct itimerval u, v;
    long t1,t2;

    switch(signo) {
	case SIGUSR1:
	    getitimer(ITIMER_REAL, &v);
	    printf("real time = %.ld secs %ld usecs\n", 9 - v.it_value.tv_sec, 999999 - v.it_value.tv_usec);
	    getitimer(ITIMER_PROF, &u);
	    printf("cpu time = %.ld secs %ld usecs\n", 9 - u.it_value.tv_sec, 999999 - u.it_value.tv_usec);
	    getitimer(ITIMER_VIRTUAL, &u);
	    printf("user time = %.ld secs %ld usecs\n", 9 - v.it_value.tv_sec, 999999 - v.it_value.tv_usec);
	    t1 = (9 - u.it_value.tv_sec) * 1000000 + (1000000 - u.it_value.tv_usec);
	    t2 = (9 - v.it_value.tv_sec) * 1000000 + (1000000 - v.it_value.tv_usec);
	    printf("Kernel time = %ld secs %ld usecs\n\n", (t1-t2)/1000000, (t1-t2)%1000000);
	    break;
	case SIGALRM:
	    printf("Timer has been zero, elapsed %d seconds\n", countsec);
	    lastsec = countsec;
	    countsec = 0;
	    break;
	default:
	    break;
    }
}

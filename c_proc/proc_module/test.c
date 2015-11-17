#include <linux/time.h>
#include <linux/unistd.h>

#define __NR_pedagogictime 238

_syscall1(int, pedagogictime, struct timeval *, thetime)

int main()
{
    struct timeval tv;

    pedagogictime(&tv);
    printf("tv_sec : %ld\n", tv.tv_sec);
    printf("tv_usec: %ld\n", tv.tv_usec);

    printf("em..., let me sleep for 2 second.\n");
    sleep(2);

    pedagogictime(&tv);
    printf("tv_sec : %ld\n", tv.tv_sec);
    printf("tv_usec: %ld\n", tv.tv_usec);

    return 1;
}

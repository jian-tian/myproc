#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define TEST_FOPEN
#define TEST_FLOCK

void *thread_flock(void *ptr)
{
    struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};
    int fd;
    int ith = *((int *)ptr);

#ifdef TEST_FOPEN
    FILE *file = NULL;
#endif

    fl.l_pid = getpid();

    while(1) {
#ifdef TEST_FOPEN
	if ((file = fopen("file_lock.c", "rw+")) == NULL) {
	    perror("fopen");
	    exit(1);
	}
#else
	if ((fd = open("file_lock.c", O_RDWR)) == -1) {
	    perror("open");
	    exit(1);
	}
#endif

#ifdef TEST_FOPEN
	fd = fileno(file);
#endif

#ifdef TEST_FLOCK
	flock(fd, LOCK_EX);
#else
	fl.l_type = F_WRLCK;
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
	    perror("fcntl");
	    exit(1);
	}

#endif
	printf("[%d] [%d] got locked\n", ith, fd);
	sleep(ith);

#ifdef TEST_FOPEN
	flock(fd, LOCK_UN);
#else
	fl.l_type = F_UNLCK;

	if (fcntl(fd, F_SETLKW, &fl) == -1) {
	    perror("fcntl");
	    exit(1);
	}
#endif
	printf("[%d] [%d] got unlocked\n", ith, fd);

#ifdef TEST_FOPEN
    fclose(file);
#else
    close(fd);
#endif

    sleep(2);
    }
    return 0;
}

void main(int argc, char **argv)
{
    int time1, time2;
    pthread_t pid1, pid2;

    time1 = 1;
    pthread_create(&pid1, NULL, &thread_flock, &time1);

    time2 = 3;
    pthread_create(&pid2, NULL, &thread_flock, &time2);

    while(1)
	sleep(10);

    return 0;
}

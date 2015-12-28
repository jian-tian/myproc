#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY 1234
#define SIZE 1024

int main(void)
{
    int shmid;
    char *shmaddr;
    struct shmid_ds buf;

    shmid = shmget(KEY, SIZE, IPC_CREAT | 0600);
    if(shmid == -1) {
	printf("create share memory failed: %s", strerror(errno));
	return 0;
    }

    if (fork() == 0) {
	shmaddr = (char *)shmat(shmid, NULL, 0);
	if ((void *)-1 == shmaddr) {
	    printf("connect to the share memory failed: %s", strerror(errno));
	    return 0;
	}
	strcpy(shmaddr, "hello, this is child process!\n");
	shmdt(shmaddr);
	return 0;
    } else {
	sleep(3);
	shmctl(shmid, IPC_STAT, &buf);
	printf(" size of the share memory: ");
	printf("shm_segsz = %d bytes \n", buf.shm_segsz);
	printf(" process id of the creator: ");
	printf("shm_cpid = %d \n", buf.shm_cpid);
	printf(" process id of the last operator: ");
	printf("shm_lpid = %d \n", buf.shm_lpid);

	shmaddr = (char *)shmat(shmid, NULL, 0);
	if ((void *)-1 == shmaddr) {
	    printf("connect to the share memory failed: %s", strerror(errno));
	    return 0;
	}
	printf("print the content of the share memory: ");
	printf("%s \n", shmaddr);

	shmdt(shmaddr);

	shmctl(shmid, IPC_RMID, NULL);
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

extern char **environ;

void *thread_proc(void *param)
{
  int first = 0;
  int *p0 = malloc(1024);
  printf("(0x%x):first = %p\n",pthread_self(),&first);
  printf("(0x%x):p0 = %p\n",pthread_self(),p0);
  return 0;
}

#define N 5

int main(int argc, char *argv[])
{
  int first = 0;
  int i = 0;
  void *ret = NULL;
  pthread_t tid[N] = {0};
  printf("first = %p\n",&first);
  for(i = 0; i<N; i++)
  {
    pthread_create(tid+i, NULL, thread_proc, NULL);
  }
  
  for(i = 0; i<N; i++)
  {
    pthread_join(tid[i], &ret);
  }
  pause();
  return 0;
}

/*
int main()
{
  char **env = environ;
  printf("environ:%p\n",environ);
  while(*env)
  {
    printf("env:%p   %p   %s\n",env,*env,*env);
    env++;
  }
}
*/

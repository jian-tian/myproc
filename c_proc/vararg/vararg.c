#include <stdio.h>
#include <stdarg.h>
const int INT_TYPE = 100000;
const int STR_TYPE = 100001;
const int CHAR_TYPE = 100002;
const int LONG_TYPE = 100003;
const int FLOAT_TYPE = 100004;
const int DOUBLE_TYPE = 100005;

void arg_type(int cnt, ...);
void arg_cnt(int cnt, ...);
void arg_test(int i, ...);

int main(int argc, char *argv[])
{
  //int int_size = _INTSIZEOF(int);
  //printf("int_size = %d\n",int_size);
  arg_test(0,4);

  arg_cnt(4,1,2,3,4);
  arg_type(2, INT_TYPE, 222, STR_TYPE, "ok,hello world");

  return 0;
}

void arg_test(int i, ...)
{
  int j = 0;
  va_list arg_ptr;

  va_start(arg_ptr, i);
  printf("&i = %p\n",&i);
  printf("arg_ptr = %p\n", arg_ptr);

  j = *((int *)arg_ptr);
  printf("%d %d\n",i,j);
  j = va_arg(arg_ptr, int);
  printf("arg_ptr = %p\n", arg_ptr);
 
  va_end(arg_ptr);
  printf("%d %d\n",i,j);
}

void arg_cnt(int cnt, ...)
{
  int value = 0;
  int i = 0;
  int arg_cnt = cnt;
  va_list arg_ptr;
  
  va_start(arg_ptr,cnt);
  for(i = 0; i < arg_cnt; i++)
  {
    value = va_arg(arg_ptr,int);
    printf("value%d=%d\n",i+1,value);
   }
  
  va_end(arg_ptr);
  return ;
}

void arg_type(int cnt, ...)
{
  int arg_type = 0;
  int int_value = 0;
  int i = 0;
  int arg_cnt = cnt;
  char *str_value = NULL;
  va_list arg_ptr;
  
  va_start(arg_ptr,cnt);
  for(i = 0; i < arg_cnt; i++)
  {
    arg_type = va_arg(arg_ptr,int);
    switch(arg_type)
    {
      case 100000:
        int_value = va_arg(arg_ptr,int);
        printf("value%d=%d\n", i+1, int_value);
        break;
      case 100001:
        str_value = va_arg(arg_ptr,char *);
        printf("value%d=%s\n",i+1,str_value);
        break;
      default:
        break;
    }
  }
  va_end(arg_ptr);
}

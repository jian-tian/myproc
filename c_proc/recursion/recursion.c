#include <stdio.h>
#define MaxSize 60
#define LAST

typedef struct
{
  char x;
  char y;
  char z;
  int flag;
  int num;
}stack;

void Hanoi1(int n, char x, char y, char z);
void Hanoi2(int n, char x, char y, char z);
void PrintHanoi(int no, char cfrom, char cto);

void main()
{
  int n;
  printf("please input the number of plates you want to move:\n");
  scanf("%d",&n);
  printf("n=%d,relization with recursion:\n", n);
  Hanoi1(n, 'X', 'Y', 'Z');
  printf("relization with non-recursion:\n");
  Hanoi2(n, 'X', 'Y', 'Z');
}

void Hanoi1(int n, char x, char y, char z)
{
  if(n == 1)
    PrintHanoi(n, x , z);
  else
   {
      Hanoi1(n-1, x, z, y);
      PrintHanoi(n, x, z);
      Hanoi1(n-1, y, x, z);
   }
}

void Hanoi2(int n, char x, char y, char z)
{
  int top = 1, x1, y1, z1, m;
  stack s[MaxSize];

  s[top].num = n; //push the problem n to stack
  s[top].flag = 1;
  s[top].x = x;
  s[top].y = y;
  s[top].z = z;

 /*while stack is not empty, do it*/
  while(top > 0)
 {
   if(s[top].flag == 1)
   {
     m = s[top].num; //pull the first problem outof stack
     x1 = s[top].x;
     y1 = s[top].y;
     z1 = s[top].z;
     top--;

     top++;          //push problem n-q into stack
     s[top].num = m - 1;
     s[top].flag = 1;
     s[top].x = y1;
     s[top].y = x1;
     s[top].z = z1;
     
     top++;
     s[top].num = m;
     s[top].flag = 0;
     s[top].x = x1;
     s[top].y = y1;
     s[top].z = z1;

     top++;
     s[top].num = m - 1;
     s[top].flag = 1;
     s[top].x = x1;
     s[top].y = z1;
     s[top].z = y1;
   }//flag == 1
   
   if(top>0 && ((s[top].flag == 0) || s[top].num == 1))
   {
      if (top > 0 && s[top].flag == 0)
      {
        PrintHanoi(s[top].num, s[top].x, s[top].z);
        top--;
      }//if(top > 0 && s[top].flag == 0)
     
      if(top > 0 && s[top].num == 1)
      {
        PrintHanoi(s[top].num, s[top].x, s[top].z);
        top--;
      }//if(top > 0 && s[top].num == 1)
   }//while(top>0 && ((s[top].flag == 0) || s[top].num == 1))
 }
}
void PrintHanoi(int no, char cfrom, char cto)
{
  printf("move number%d from %c to %c\n", no, cfrom, cto);
}

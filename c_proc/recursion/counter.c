#include <stdio.h>
#include <string.h>

typedef char DataType;
#include "SeqStack.h"
#define MaxSize 60

typedef struct
{
  float data[MaxSize];
  int top;
}OpStack;

void TranslateExpress(char s1[], char s2[]);
float ComputeExpress(char s[]);

void main()
{
  char a[MaxSize], b[MaxSize];
  float f;
  printf("please input a express:\n");
  gets(a);
  printf("mid express is : %s\n", a);
  TranslateExpress(a, b);
  printf("after express is :%s\n", b);
  f = ComputeExpress(b);
  printf("the result is :%f\n", f); 
}

float ComputeExpress(char a[])
{
  Opstack S;
  int i = 0, value;
  float x1, x2;
  float result;
  S.top = -1;
  
  while(a[i] != '\0')
  {
    if(a[i] != ' ' && a[i] >= '0' && a[i] <= '9')
    {
      value = 0;
      while(a[i] != ' ')
      {
        value = 10*value + a[i] - '0';
        i++;
      }//while(a[i] != ' ')
      S.top++;
      S.data[S.top] = value;
    }
    else
    {
      switch(a[i])
      {
        case '+':
          x1 = S.data[S.top];
          S.top--;
          x2 = S.data[S.top];
          S.top--;
          result = x1 + x2;
          S.top++;
          S.data[S.top] = result;
          break;
        case '-':
          x1 = S.data[S.top];
          S.top--;
          x2 = S.data[S.top];
          S.top--;
          result = x1 - x2;
          S.top++;
          S.data[S.top] = result;
          break;
        case '*':
          x1 = S.data[S.top];
          S.top--;
          x2 = S.data[S.top];
          S.top--;
          result = x1 * x2;
          S.top++;
          S.data[S.top] = result;
          break;
         case '/':
          x1 = S.data[S.top];
          S.top--;
          x2 = S.data[S.top];
          S.top--;
          result = x1 / x2;
          S.top++;
          S.data[S.top] = result;
          break;
      }//switch(a[i])
      i++;
    }//if(a[i] != ' ' && a[i] >= '0' && a[i] <= '9')
  }//while(a[i] != '\0')
  
  if(!S.top != -1)
  {
    result = S.data[S.top];
    S.top--;
    if(S.top == -1)
      return result;
    else
    {
      printf("express error!\n");
      exit(-1);
    }
  }//if(!S.top != -1)
}

void TranslateExpress(char str[], char exp[])
{
  SeqStack S;
  char ch;
  DataType e;
  int i = 0, j = 0;

  InitStack(&S);
  ch = str;
  i++;
  
  while(ch != '\0')
  {
    switch(ch)
    {
      case '(':
        PushStack(&S, ch);
        break;

      case ')':
        while(GetTop(S,&e) && e!= '(')
        {
          PopStack(&S, &e);
          exp[j] = e;
          j++;
        }//while(GetTop(S,&e) && e!= '(')
        PopStack(&S, &e);
        break;

      case '+':
      case '-':
        while(!StackEmpty(S) && GetTop(S,&e) && e != '(')
        {
          PopStack(&S, &e);
          exp[j] = e;
          j++;
        }//while(!StackEmpty(S) && GetTop(S,&e) && e != '(')
        PushStack(&S, &e);
        break;
  
      case '/':
        while(!StackEmpty(S) && GetTop(S,&e) && e == '/' || e == '*')
        {
          PopStack(&S, &e);
          exp[j] = e;
          j++;
        }
        PushStack(&S, ch);
        break;

      case ' ';
        break;

      default:
        while(ch >= '0' && ch <= '9')
        {
          exp[j] = ch;
          j++;
          ch = str[i];
          i++;
        }
        i--;
        exp[j] = ' ';
        j++;
    }//case
    ch = str[i];
    i++;
  }//while(ch != '\0')
  
  while(!StackEmpty(S))
  {
    PopStack(&S, &e);
    exp[j] = e;
    j++;
  }
  exp[j] = '\0';
} 

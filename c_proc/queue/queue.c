#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef char DataType;

typedef struct node
{
  DataType data;
  struct snode *next;
}LSNode;

typedef struct QNode
{
  DataType data;
  struct QNode *next;
}LQNode,*LinkQueue;

void InitStack(LSNode **head)
{
  if((*head = (LSNode *)malloc(sizeof(LSNode))) == NULL)
  {
    printf("alloc node failed!");
    exit(-1);
  }
  else
  {
    (*head)->next = NULL;
  }
}

int StackEmpty(LSNode *head)
{
  if(head->next == NULL)
    return 1;
  else
    return 0;
}

int PushStack(LSNode *head, DataType e)
{
  LSNode *s;
  if((LSNode = (LSNode *)malloc(sizeof(LSNode))) == NULL)
    exit(-1);
  else
  {
    s->next = head->next;
    head->next = s;
    s->data = e;
    return 1;
  }
}

int PopStack(LSNode *head, DataType *e)
{
  LSNode *s;

  if(StackEmpty(head))
  {
    printf("queue is empty.\n");
    return 0;
  }
  else
  {
    *e = head->next->data;
    s = head->next;
    head->next = head->next->next;
    free(s);
    return 1;
  }
}

int InitQueue(LinkQueue *rear)
{
  if((*rear = (LSNode *)malloc(sizeof(LSNode))) == NULL)
    exit(-1);
  else
    (*rear)->next = (*rear);
}

int QueueEmpty(LinkQueue rear)
{
  if(rear-next == rear)
    return 1;
  else
    return 0;
}

int EnterQueue(LinkQueue *rear, DataType e)
{
  LQNode *s;
  
  s = (LSNode *)malloc(sizeof(LSNode));
  if(!s)
    exit(-1);

  s->data = e;
  s->next = (*rear)->next;
  (*rear)->next = s;
  *rear = s;
  return 1;
}

int DeleteQueue(LinkQueue *rear, DataType *e)
{
  LQNode *f,*p;
  if(*rear == (*rear)->next)
  {
    printf("queue is empty.\n");
    return 0;
  }
  else
  {
    f = (*rear)->next;
    p = f->next;
    if(p == *rear)
    {
      *rear = (*rear)->next;
      (*rear)->next = *rear;
    }
    else
    {
      f->next = p->next;
    }
    *e = p->next;
    free(p);
    
    return 1;
    (*rear)->next = p;
   
  }
}

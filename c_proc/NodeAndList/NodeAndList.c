/**header files**/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/**structe define**/
struct Node
{
  char name[10];
  int score;
  struct Node *next;  
};
typedef struct Node ListNode;

/**function declaration**/
ListNode *CreateList(int n);
void InsertList(ListNode *h, int i, char name[], int score, int n);
void DeleteList(ListNode *h, int i, int n);
void PrintList(ListNode *h);

/**realization of function**/
/**create list**/
ListNode *CreateList(int n)
{
  ListNode *head;
  ListNode *p,*pre;
  int i;

  head = (ListNode *)malloc(sizeof(ListNode));
  head->next = NULL;
  pre = head;

  for(i = 1; i <= n; i++)
  {
    printf("input name of the %d student:\n",i);
    p = (ListNode *)malloc(sizeof(ListNode));
    scanf("%s", &p->name);
    printf("input score of the %d student:\n",i);
    scanf("%d", &p->score);
    pre->next = p;
    pre = p;
  }
  p->next = NULL;
  
  return head;  
}

/**print list**/
void PrintList(ListNode *h)
{
  ListNode *p;
  p = h->next;

  while(p)
  {
    printf("%s %d\n", p->name, p->score);
    p = p->next;
  }
}

/**main function**/
void main()
{
  ListNode *h;
  int i = 1, n, score;
  char name[10];

  while(1)
  {
    printf("1----create new List\n");
    printf("2----add element\n");
    printf("3----delete element\n");
    printf("4----print the elements of list\n");
    printf("0----quit\n");
    
    scanf("%d", &i);
    switch(i)
    {
    case 1:
      printf("n=");
      scanf("%d",&n);
      h = CreateList(n);
      printf("list element is:\n");
      PrintList(h);
      break;
    case 2:
      printf("input the position. of insert element:");
      scanf("%d",&i);
      printf("input the name of the student:");
      scanf("%s",&name);
      printf("input score of the student:");
      scanf("%d",&score);
      InsertList(h, i, name, score, n);
      printf("list element is:\n");
      PrintList(h);
      break;
    case 3:
      printf("input the position of delete element:");
      scanf("%d",&i);
      DeleteList(h, i, n);
      printf("list element is:\n");
      PrintList(h);
      break;
    case 4:
      printf("list element is:\n");
      PrintList(h);
      break;
    case 0:
      return;
      break;
    default:
      printf("ERROR! Try again!\n\n");
    }
  }
}

/**Insert element to List**/
void InsertList(ListNode *h, int i, char name[], int e, int n)
{
  ListNode *q, *p;
  int j;
  if( i<1 || i>n+1)
    printf("Error!Please input again:\n");
  else
  {
    j = 0;
    p = h;
    while(j < i-1)
    {
      p = p->next;
      j++;
    }  
    q = (ListNode *)malloc(sizeof(ListNode));
    strcpy(q->name, name);
    q->score = e;
    q->next = p->next;
    p->next = q;
  }
}

/**delete element form List**/
void DeleteList(ListNode *h, int i, int n)
{
  ListNode *p, *q;
  int j;
  char name[10];
  int score;
  if(i<1 || i>n+1)
    printf("Error! Please input again:");
  else
  {
    j = 0;
    p = h;
    while(j < i - 1)
    {
      p = p->next;
      j++;
    }
    q = p->next;
    p->next = q->next;
    strcpy(name, p->name);
    score = q->score;
    free(q);
    printf("name = %s, score = %d\n", name ,score);
  }
}

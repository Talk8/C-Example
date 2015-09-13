# 一起talk C栗子吧（第二十三回：C语言实例--队列二）

各位看官们，大家好，上一回中咱们说的是队列及其特点，并且通过例子来说明队列，这一回咱们继续说
队列，不过咱们说的是链式存储形式的队列，这与上一回中顺序存储形式的队列不一样。闲话休提，言归
正转。让我们一起talk C栗子吧！ 

在代码中通过链表来实现队列的链式存储。而且定义了一个头结点，头结点主要用来保存队列的头部和尾
部信息，以及队列的长度信息。我们对队列的操作，本质上是对链表进行操作，队列中的结点可以看作是
链表中的结点，对队列进行入列（EnQueue）和出列（DeQueue）的操作，可以看作是在链表中进行插入
或者删除结点操作。只不过插入或者删除时要遵循队列“先进先出"的特点。

队列的链式存储与队列的顺序存储相比，最大的优点就是不需要事先知道队列的长度，也正是因为这点原
因，在实际的程序中，使用较多的是通过链式存储实现的队列。此外，它比顺序存储方式实现的队列要灵
活一些，比如入列和出列的操作也很方便。它的空间利用率比顺序存储方式实现的队列要高很多。试想一
下，一个长度为10的顺序容器（程序中是数组），只用来存放长度为3的队列，明显浪费了容器中7个存储
空间。还有就是如果队列的长度超过顺序容器的长度时，还需要重新调整顺序容器的长度，不然它会因为
长度不足，没有空间来存放整个队列。

看官们，详细的代码如下所示，大家可以参考：
```
     1	/* **************************
     2	 * Head file of Queue
     3	 * *************************/
     4	#ifndef QUEUE_H
     5	#define QUEUE_H
     6	
     7	#include<stdio.h>
     8	#include<stdlib.h>
     9	
    10	#define SUCCESS 0
    11	#define FAILE 1
    12	
    13	typedef int QueueElmt; //把int当作队列中元素的类型，实际中可以使用其它的类型或者自己定义一个元素类型
    14	typedef struct _QueueNode {
    15		QueueElmt elmt;
    16		struct _QueueNode *next;
    17	}QueueNode;
    18	
    19	typedef struct _Queue{
    20		QueueNode *front; //指向队列的头结点
    21		QueueNode *rear;  //指向队列的尾结点,队列中只有一个元素时头尾指针相同
    22		int size;
    23	}Queue;
    24	
    25	
    26	//声明函数原型
    27	int QueueInit(Queue *q);
    28	int QueueDestroy(Queue *q);
    29	int QueuePrint(Queue *q);
    30	int EnQueue(Queue *q,QueueElmt e);
    31	int DeQueue(Queue *q,QueueElmt *e);
    32	
    33	#endif /*QUEUE_H*/
```
```
     1	/* **************************
     2	 * Soure file of Queue
     3	 * *************************/
     4	
     5	#include"Queue2.h"
     6	
     7	//实现Queue的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	int QueueInit(Queue *q)
     9	{
    10		if(NULL == q)
    11			return FAILE;
    12	
    13		q->front = q->rear = NULL;
    14		q->size = 0;
    15	
    16		return SUCCESS;
    17	}
    18	
    19	int QueueDestroy(Queue *q)
    20	{
    21		QueueNode *temp = NULL;
    22	
    23		if(NULL == q)
    24			return FAILE;
    25	
    26		if(q->size == 0)
    27		{
    28			printf("Queue is empty \n");
    29			return SUCCESS;
    30		}
    31	
    32		while(q->size >0)
    33		{
    34			temp = q->front;
    35			q->front = temp->next;
    36			temp->next = NULL;
    37			free(temp);
    38			q->size -= 1;
    39		}
    40		q->front = q->rear = NULL;
    41	
    42		return SUCCESS;
    43	}
    44	
    45	int QueuePrint(Queue *q)
    46	{
    47		QueueNode *temp = NULL;
    48	
    49		if(NULL == q)
    50			return FAILE;
    51	
    52		if(q->size == 0)
    53		{
    54			printf("Queue is empty \n");
    55			return SUCCESS;
    56		}
    57	
    58		printf("Elmt of Queue:");
    59		temp = q->front;
    60		while(temp != NULL)
    61		{
    62			printf("%d  ",temp->elmt);
    63			temp = temp->next;
    64		}
    65		printf("\n");
    66	
    67		return SUCCESS;
    68	}
    69	
    70	int EnQueue(Queue *q,QueueElmt e)
    71	{
    72		QueueNode *node;
    73	
    74		if(NULL == q)
    75			return FAILE;
    76	
    77	
    78		node = (QueueNode*)malloc(sizeof(QueueNode));
    79		if( NULL != node)
    80		{
    81			if(q->size == 0)
    82				q->front = q->rear = node;
    83			else
    84			{
    85				q->rear->next = node;
    86				q->rear = node;
    87			}
    88	
    89			node->elmt = e;
    90			node->next = NULL;
    91			q->size +=1;
    92	
    93			return SUCCESS;
    94		}
    95		else
    96			return FAILE;
    97	}
    98	
    99	int DeQueue(Queue *q,QueueElmt *e)
   100	{
   101		QueueNode * node;
   102	
   103		if(NULL == q)
   104			return FAILE;
   105	
   106		if(q->size > 0 )
   107		{
   108			node = q->front;
   109			*e = node->elmt;
   110			q->front = node->next;
   111			q->size -=1;
   112	
   113			node->elmt =0;
   114			node->next = NULL;
   115			free(node);
   116	
   117			return SUCCESS;
   118		}
   119		else
   120			return FAILE;
   121	}
   122	
   123	int main()
   124	{
   125		int i = 0;
   126		int result =0;
   127		QueueElmt e;
   128		Queue queue;
   129	
   130		QueueInit(&queue);
   131		QueuePrint(&queue);
   132	
   133		while(i<5)
   134			EnQueue(&queue,(++i));
   135	
   136		result = EnQueue(&queue,9);
   137		if(FAILE == result)
   138			printf("EnQueue is failed \n");
   139		else
   140			QueuePrint(&queue);
   141	
   142	
   143		DeQueue(&queue,&e);
   144		printf("%d is deleted from Queue \n",e);
   145		QueuePrint(&queue);
   146	
   147		DeQueue(&queue,&e);
   148		printf("%d is deleted from Queue \n",e);
   149		QueuePrint(&queue);
   150	
   151		DeQueue(&queue,&e);
   152		printf("%d is deleted from Queue \n",e);
   153		QueuePrint(&queue);
   154	
   155		DeQueue(&queue,&e);
   156		printf("%d is deleted from Queue \n",e);
   157		QueuePrint(&queue);
   158	
   159		DeQueue(&queue,&e);
   160		printf("%d is deleted from Queue \n",e);
   161		QueuePrint(&queue);
   162	
   163		DeQueue(&queue,&e);
   164		printf("%d is deleted from Queue \n",e);
   165		QueuePrint(&queue);
   166	
   167		result = DeQueue(&queue,&e);
   168		if(FAILE == result)
   169			printf("DeQueue is failed \n");
   170	
   171		QueueDestroy(&queue);
   172		QueuePrint(&queue);
   173	
   174		return result;
   175	}
```

各位看官，关于队列的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

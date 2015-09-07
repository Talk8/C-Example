# 一起talk C栗子吧（第二十二回：C语言实例--队列一）

各位看官们，大家好，上一回中咱们说的是表达式求值的例子，该例子使用了栈，这一回咱们说的是栈的兄弟：队列。闲话休提，言归正转。让我们一起talk C栗子吧！ 

我们在这里说的队列是一种抽象的数据结构，大家不用想的太抽象了，哈哈，其实它和我们日常生活中所
见的队列一样。不管怎么样，我们还是举一个容易理解的例子：大家在假期出去旅游的时候，都有过排队
买门票的经历吧。游客们在售票点的窗口前排成了一长串队列，售票人员先把门票卖给排在队列前面的游
客，买到门票的游客拿着门票兴高采烈地离开了队列，刚来到售票点的游客排在队列尾部默默地等着购买
门票。在这个例子中，游客们为了购买门票在售票点旁边排成一条长队，这条长队可以看作是队列，队列
里的游客可以看作是队列中存放的元素。买到门票的游客离开队列，可以看作是从队列中删除元素，想要
购买门票的游客排到队列里，可以看作是向队列中插入元素。我这么，大家还觉得队列抽象吗？如果觉
得抽象的话，下次旅游购买门票时多留意一下就可以。

我们来说一下队列的特点：

- 1.队列有头也有尾。比如刚才例子中，先购买到门票的游客可以看作是队列头部。刚刚排到队列里的游客可以看作是队列的尾部。
- 2.从队列中删除元素只能在队列头部进行。比如刚才例子中购买到门票的游客离开队列，可以看作是从队列头部删除了一个元素。
- 3.向队列中插入元素只能在队列尾部进行。比如刚才例子中想要购买门票的游客排到队列里，可以看作是向队列中插入一个元素。
- 4.队列中的元素遵守”先进先出“的规则。比如刚才例子中先排队的游客可以先购买到门票。

看官们，详细的代码如下，大家请参考。这个队列是通过顺序存储的方式实现的，具体到代码中是使用了一个数组来从充当队列。

```
     1	/* **************************
     2	 * Head file of Queue
     3	 * *************************/
     4	#ifndef QUEUE_H
     5	#define QUEUE_H
     6	
     7	#include<stdio.h>
     8	
     9	#define SUCCESS 0
    10	#define FAILE 1
    11	
    12	#define LEN 5 //队列的长度先定义为5,需要时可自行修改 
    13	
    14	typedef int QueueElmt; //把int当作队列中元素的类型，实际中可以使用其它的类型或者自己定义一个元素类型
    15	typedef struct _Queue{
    16		QueueElmt *front;
    17		QueueElmt *rear;
    18	}Queue;
    19	
    20	QueueElmt QUEUE[LEN] = {0}; //顺序存储方式的队列
    21	
    22	//声明函数原型
    23	int QueueInit(Queue *q);
    24	int QueuePrint(Queue *q);
    25	int EnQueue(Queue *q,QueueElmt e);
    26	int DeQueue(Queue *q,QueueElmt *e);
    27	
    28	#endif /*QUEUE_H*/
```

```
     1	/* **************************
     2	 * Soure file of Queue 
     3	 * *************************/
     4	
     5	#include"Queue1.h"
     6	
     7	//实现Queue的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	int QueueInit(Queue *q)
     9	{
    10		if(NULL == q)
    11			return FAILE;
    12	
    13		q->front = q->rear = &QUEUE[0];
    14	
    15		return SUCCESS;
    16	}
    17	
    18	int QueuePrint(Queue *q)
    19	{
    20		QueueElmt *temp = NULL;
    21	
    22		if(NULL == q)
    23			return FAILE;
    24	
    25		if(q->front == q->rear)
    26		{
    27			printf("Queue is empty \n");
    28			return SUCCESS;
    29		}
    30	
    31		printf("Elmt of Queue:");
    32		temp = q->front;
    33		while(temp != q->rear)
    34			printf("%d  ",*temp++);
    35		printf("\n");
    36	
    37		return SUCCESS;
    38	}
    39	
    40	int EnQueue(Queue *q,QueueElmt e)
    41	{
    42		if(NULL == q)
    43			return FAILE;
    44	
    45		if(LEN > (q->rear - q->front))
    46		{
    47			*(q->rear) = e;
    48			q->rear++;
    49	
    50			return SUCCESS;
    51		}
    52		else
    53			return FAILE;
    54	}
    55	
    56	int DeQueue(Queue *q,QueueElmt *e)
    57	{
    58		if(NULL == q)
    59			return FAILE;
    60	
    61		if(0 < (q->rear - q->front))
    62		{
    63			*e = *(q->front);
    64			*(q->front) = 0;
    65			q->front++;
    66	
    67			return SUCCESS;
    68		}
    69		else
    70			return FAILE;
    71	}
    72	
    73	int main()
    74	{
    75		int i = 0;
    76		int result =0;
    77		QueueElmt e;
    78		Queue queue;
    79	
    80		QueueInit(&queue);
    81		QueuePrint(&queue);
    82	
    83		while(i<LEN)
    84			EnQueue(&queue,(++i));
    85	
    86		result = EnQueue(&queue,9);
    87		if(FAILE == result)
    88			printf("EnQueue is failed \n");
    89	
    90		QueuePrint(&queue);
    91	
    92		DeQueue(&queue,&e);
    93		printf("%d is deleted from Queue \n",e);
    94		QueuePrint(&queue);
    95	
    96		DeQueue(&queue,&e);
    97		printf("%d is deleted from Queue \n",e);
    98		QueuePrint(&queue);
    99	
   100		DeQueue(&queue,&e);
   101		printf("%d is deleted from Queue \n",e);
   102		QueuePrint(&queue);
   103	
   104		DeQueue(&queue,&e);
   105		printf("%d is deleted from Queue \n",e);
   106		QueuePrint(&queue);
   107	
   108		DeQueue(&queue,&e);
   109		printf("%d is deleted from Queue \n",e);
   110		QueuePrint(&queue);
   111	
   112		DeQueue(&queue,&e);
   113		printf("%d is deleted from Queue \n",e);
   114		QueuePrint(&queue);
   115	
   116		result = DeQueue(&queue,&e);
   117		if(FAILE == result)
   118			printf("DeQueue is failed \n");
   119		return result;
   120	}
```

各位看官，关于队列的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

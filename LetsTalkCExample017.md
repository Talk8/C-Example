# 一起talk C栗子吧（第十七回：C语言实例--栈二）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是栈和特点和基本操作，最后通过顺序存储的方式实现了栈，这一回咱们继续
说栈，不过咱们这一回说的是栈的链式存储方式。

在代码中通过双向链表来实现栈的链式存储。入栈操作沿着表头到表尾的方向进行，出栈操作与其正好相
反（就把它当作双向链表的一个使用实例吧）。栈的结点可以看作是链表中的结点，对栈的操作，可以看
作是在链表中进行插入或者删除结点操作。只不过插入或者删除时要遵循栈“先进后出"的特点。栈的类型
中增加了一个size成员，可以通过它方便地得出栈的长度。与栈的顺序存储方式相比，多了一个销毁栈的
功能。因为栈中的空间都是动态分配得来的，每次入栈操作都会分配一块内存空间，与其相反，每次出栈
操作都会把内存空间释放掉。但是在实际程序中入栈和出栈并不是成对出现的，也就是说，如果使用完栈
后，没有通过出栈操作来释放动态空间，那么就会造成内存泄漏。所以我增加了销毁栈的功能，以方便在
程序的最后检查栈中动态分配来的空间是否被释放。

栈的链式存储与栈的顺序存储相比，最大的优点就是不需要事先知道栈的长度，只要内存空间足够大就能
存放足够多的元素到栈中。不过，它也有缺点，那就是入栈和出栈操作要复杂，而且效率低。总之，在实
际的程序中如果事先知道栈的长度，可以使用栈的顺序存储，如果与事先不知道栈的长度，那么可以使用
栈的链式存储，这样比较灵活一些。

看官们，详细的代码如下，大家可以参考：

```
     1	/* **************************
     2	 * Head file of Stack
     3	 * *************************/
     4	#ifndef STACK_H
     5	#define STACK_H
     6	
     7	#include<stdio.h>
     8	#include<stdlib.h>
     9	
    10	#define SUCCESS 0
    11	#define FAILE 1
    12	
    13	typedef struct _StackElmt
    14	{
    15		int data;
    16		struct _StackElmt *pre;
    17		struct _StackElmt *next;
    18	}StackElmt; //把int当作栈中元素的类型，实际中可以使用其它的类型或者自己定义一个类型
    19	
    20	typedef struct _Stack{
    21		StackElmt *base; //栈底指针
    22		StackElmt *top;  //栈顶指针，它指向的区域存放StackElmt类型的值
    23		int size;        //方便统计栈的长度
    24	}Stack;
    25	
    26	//声明函数原型，这里有入栈和出栈操的函数
    27	int StackInit(Stack *s);
    28	int StackPrint(Stack *s);
    29	int StackPush(Stack *s, int e);
    30	int StackPop(Stack *s, int *e);
    31	int StackDestroy(Stack *s);
    32	
    33	#endif /*STACK_H*/
```

```
     1	/* **************************
     2	 * Soure file of Stack
     3	 * *************************/
     4	
     5	#include"Ex015_Stack2.h"
     6	
     7	//实现List的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	//
     9	//初始化中栈
    10	int StackInit(Stack *s)
    11	{
    12		if(NULL == s)
    13			return FAILE;
    14	
    15		s->top = s->base = NULL;
    16		s->size = 0;
    17	
    18		return SUCCESS;
    19	}
    20	
    21	//输出栈中存放的元素
    22	int StackPrint(Stack *s)
    23	{
    24		int index = 0;
    25		StackElmt *t = NULL;
    26	
    27		if(NULL == s)
    28			return FAILE;
    29	
    30		if(s->size == 0)
    31		{
    32			printf("the Stack is empty,there is not any element \n");
    33			return FAILE;
    34		}
    35	
    36		t = s->base;
    37		while(NULL != t)
    38		{
    39			printf("%d  ",t->data);
    40			t = t->next;
    41		}
    42	
    43		printf("\n ");
    44	
    45		return SUCCESS;
    46	}
    47	
    48	//入栈函数,top指向栈顶,每次push操作都会分配一个空间，top永远指向该空间
    49	int StackPush(Stack *s, int e)
    50	{
    51		StackElmt *node = NULL;
    52	
    53		if(NULL == s)
    54			return FAILE;
    55	
    56		node = (StackElmt *)malloc( sizeof(StackElmt) );
    57	
    58		if(NULL != node)
    59		{
    60			if(NULL == s->base)
    61			{
    62				s->top = s->base = node;
    63				node->pre = NULL;
    64			}
    65			else
    66			{
    67				(s->top)->next = node;
    68				node->pre = s->top;
    69				s->top = node; //相当于顺序存储中的top++
    70			}
    71	
    72			node->data = e;
    73			node->next = NULL;
    74			(s->size)++;
    75	
    76			return SUCCESS;
    77		}
    78		else
    79			return FAILE;
    80	}
    81	
    82	//出栈函数,先把top指向的元素出栈，然后释放top指向的空间
    83	int StackPop(Stack *s, int *e)
    84	{
    85		StackElmt *t = NULL;
    86	
    87		if(NULL == s)
    88			return FAILE;
    89	
    90		if(s->size == 0)
    91		{
    92			printf("the Stack is empty \n");
    93			return FAILE;
    94		}
    95	
    96		*e = (s->top)->data ;
    97		t = (s->top)->pre;
    98		free(s->top);
    99		s->top = t; //相当于top--
   100	
   101		if(s->size == 1) //最后一个元素出栈时，base和top都为NULL
   102			s->base = s->top;
   103	
   104		(s->size)--;
   105	
   106		return SUCCESS;
   107	}
   108	
   109	//栈销毁函数，因为有动态分配的空间，如果不执行出栈操作，要把栈destroy
   110	int StackDestroy(Stack *s)
   111	{
   112		int t = 0;
   113		int result = 0;
   114	
   115		if(NULL == s)
   116			return FAILE;
   117	
   118		while(NULL != (s->base) )
   119			result = StackPop(s,&t);
   120	
   121		return result;
   122	}
   123	
   124	int main()
   125	{
   126		int i = 0;
   127		int e = 0;
   128		Stack stack ;
   129	
   130		if( SUCCESS == StackInit(&stack) )
   131			StackPrint(&stack);
   132	
   133		StackPush(&stack,7);
   134		StackPrint(&stack);
   135	
   136		StackPop(&stack,&e);
   137		printf("%d is poped \n",e);
   138	
   139		while(i++ < 5)
   140		{
   141			if( SUCCESS == StackPush(&stack,i) )
   142				printf("%d is pushed \n",i);
   143			else
   144				printf("push failed \n");
   145		}
   146	
   147		while(i-- > 0)
   148		{
   149			if( SUCCESS == StackPop(&stack,&e) )
   150				printf("%d is poped \n",e);
   151			else
   152				printf("pop failed \n");
   153		}
   154	
   155		if( SUCCESS == StackDestroy)
   156			printf("Stack destroy successfully  \n");
   157		else
   158			printf("Stack need not to destroy  \n");
   159	
   160	}
```

各位看官，关于栈的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

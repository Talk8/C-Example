# 一起talk C栗子吧（第十六回：C语言实例--栈一）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是双向链表的例子，这一回咱们说的例子是：栈。

什么是栈？我们听过龙门客栈，你这个是哪家客栈？我还没有说，台下已经有客官在问了。看官们，栈是
类似我们在前面几回中说过的链表，它也是用来存放数据的一种抽象的数据结构。因为比较抽象，咱们还
是举个现实生活中的例子来说明吧。我们出去旅游时通常拿一个行李箱存放自己的物品，比如衣服，鞋子
电脑，相机等。出发前，我们会把这些东西依次放到行李箱中，首先会把不容易压坏的物品放到箱底，比
如衣服。然后把容易压坏的物品放到上面，比如电脑和相机。当我们到达目的地时，会取出行李箱中的物
品。首先拿出放在箱子上面的电脑和相机，最后拿出放在箱子底部的衣服。大家看看，拿出物品的顺序和
存放物品的顺序正好相反。最后放进去的电脑和相机等易压碎的物品最先拿出来，最先放进去的衣服等不
易压碎的物品最后拿出来。这个行李箱就好比一个存放数据的栈，箱子里面的物品好比数据，从箱子里拿
物品好比操作数据，拿物品要先拿最后存放的物品，操作数据也要先操作最后放到栈中的数据。就是说最
先存放到栈中的数据最后被拿出。这便是栈的特点：先进后出。

看官们，和链表一样，栈也有两种实现方式：顺序存放和链式存放。我们会分别举例子说明。栈有两个基
本的操作：出栈和入栈。入栈就是把数据存放到栈中，出栈就是把数据从栈中拿出来。入栈和出栈这两个
操作要符合栈“先进后出”的特点。

看官们，详细的代码如下，大家可以参考。关于代码中有一些需要注意的地方和大家说一下：

- 1.栈的顺序存储是通过一个全局数组实现的，栈的大小就也就是数组的长度，可以自己定义。
- 2.入栈时要确认栈是否已经満了，不然会有溢出。我在代码中多放了一个空间可以避免溢出。
- 3.出栈时要确认栈是否已经空了，不然会有溢出。我在代码中通过多放了一个变量size可以避免溢出。
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
    13	#define LEN 5 //栈的长度先定义为5,需要时可自行修改
    14	
    15	typedef int StackElmt; //把int当作栈中元素的类型，实际中可以使用其它的类型或者自己定义一个List类型
    16	typedef struct _Stack{
    17		StackElmt *base;
    18		StackElmt *top;
    19		int size;
    20	}Stack;
    21	
    22	StackElmt STACK[LEN+1] = {0}; //顺序存储方式的栈,防止数组越界，最后一个位置不放元素
    23	
    24	//声明函数原型，这里有入栈和出栈操的函数
    25	int StackInit(Stack *s);
    26	int StackPrint(Stack *s);
    27	int StackPush(Stack *s, StackElmt e);
    28	int StackPop(Stack *s, StackElmt *e);
    29	
    30	#endif /*STACK_H*/
```

```
     1	/* **************************
     2	 * Soure file of Stack
     3	 * *************************/
     4	
     5	#include"Stack1.h"
     6	
     7	//实现List的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	//初始化中栈
     9	int StackInit(Stack *s)
    10	{
    11		if(NULL == s)
    12			return FAILE;
    13	
    14		s->top = s->base = &STACK[0];
    15		s->size = 0;
    16	
    17	}
    18	//输出栈中存放的元素
    19	int StackPrint(Stack *s)
    20	{
    21		int index = 0;
    22	
    23		if(NULL == s)
    24			return FAILE;
    25	
    26		if(s->size == 0)
    27		{
    28			printf("the Stack is empty,there is not any element \n");
    29			return FAILE;
    30		}
    31	
    32		while(index < (s->size))
    33		{
    34			printf("%d  ",*((s->base)+index) );
    35			index++;
    36		}
    37	
    38		printf("\n ");
    39	
    40		return SUCCESS;
    41	}
    42	
    43	//入栈函数,top指向栈顶,先把元素入栈,然后向栈顶移动一位
    44	int StackPush(Stack *s, StackElmt e)
    45	{
    46		if(NULL == s)
    47			return FAILE;
    48	
    49		if(s->size >= LEN)
    50		{
    51			printf("the Stack is full \n");
    52			return FAILE;
    53		}
    54	
    55		*(s->top) = e;
    56		(s->top)++;
    57		(s->size)++;
    58	
    59		return SUCCESS;
    60	}
    61	
    62	//出栈函数,top先向栈底移到一位，然后移出当前它所指向的元素
    63	int StackPop(Stack *s, StackElmt *e)
    64	{
    65		if(NULL == s)
    66			return FAILE;
    67	
    68		if(s->size == 0)
    69		{
    70			printf("the Stack is empty \n");
    71			return FAILE;
    72		}
    73	
    74		(s->top)--;
    75		*e = *(s->top);
    76		(s->size)--;
    77	
    78		return SUCCESS;
    79	}
    80	
    81	
    82	int main()
    83	{
    84		int i = 0;
    85		StackElmt e = 0;
    86		Stack stack ;
    87	
    88		if( SUCCESS == StackInit(&stack) )
    89			StackPrint(&stack);
    90	
    91		StackPush(&stack,7);
    92		StackPrint(&stack);
    93	
    94		StackPop(&stack,&e);
    95		printf("%d is poped \n",e);
    96	
    97		while(i++ < LEN+5)
    98		{
    99			if( SUCCESS == StackPush(&stack,i) )
   100				printf("%d is pushed \n",i);
   101		}
   102	
   103		while(i-- > 0)
   104		{
   105			if( SUCCESS == StackPop(&stack,&e) )
   106				printf("%d is poped \n",e);
   107		}
   108	
   109	}
```

各位看官，关于栈的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

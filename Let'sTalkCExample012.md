## 一起talk C栗子吧（第十二回：C语言实例--单链表一）
 
 各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  

 看官们，上一回中咱们没有说具体的例子，而且是说了例子中的文件组织结构。这一回咱们继续说C例子，
说的例子是链表，更准确的说法叫作单链表。咱们不但要说C例子，而且会在例子中使用上一回中说过的
文件组织结构，就当作是举例说明文件组织结构的使用方法。 有点一石二鸟的感觉，哈哈。 
 
 **链表定义**：看官们，所谓的链表其实就是一组元素通过一定的方式链接在一起。比如我们坐的火车和地铁，
就是把一节节的车厢链接在一起才形成了一个火车或者地铁。在软件开发中常用的链表有单链表，双向链
表和循环链表。今天，我们主要说的是单链表，其它类型的链表在后面的章回中依次介绍。 
 
 **链表实现**：单链表有两种实现方法，一种是线性存储，一种是链式存储。这么说，大家可能可能觉得有点
抽象，不容易理解。没关系，咱们用举个生活中的例子说明。线性存储可以看作元素一个接一个的排列在
一起，我们日常生活中的排队就可以看作是线性存储，队列中的每个人看作是链表中的元素，排队时每个
人都是一个跟着一个，生怕中间有个空间被其它人插队，这种一个跟着一个的方式可以看作是线性存储。
在写程序的时候，使用数组来表示单链表的线性存储。数组中的元素大小相同，而且各个元素依次排列在
一起，通过数组下标可以访问数组中的元素。链式存储可以看作元素通过一条链连接在一起，我们日常生
活中马路上的车队可以看作是链式存储。每当上下班高峰的时候，马路上的车辆都是一个接一个地在马路
上缓慢行走，远远望去就是一条汽车链。每辆汽车可以看作链表中的元素，而这条汽车链就是通过马路连
接在一起的。当然了，这些汽车里有一些公交车，它们会在路边公交车站临时停车，供乘客上下车。但是
不会影响其它汽车在马路上行走。我们把公交车停在公交车站的当作从汽车链中删除一个元素。当公交车
离开公交车站回到马路上时，可以看作是向汽车链中插入一个元素。看官们能感觉到公交车在公交车站的
停靠，对汽车链的影响非常小。这也体现了单链表的好处，删除或者插入元素很方便。哈哈，把日常生活
中的东西和链表这个抽象的概念结合起来，是不是感觉理解容易了呢？ 
  
 看官们，关于的单链表的例子，详细的代码如下，大家可以参考。在例子中能看到：通过数组来实现单链
 表的顺序储存方式，同时提供了单链表常用的功能：遍历链表，插入和删除元素，查找元素。  
 ```
     1	/* **************************
     2	 * Head file of Single List
     3	 * *************************/
     4	#ifndef SINGLE_LIST_H
     5	#define SINGLE_LIST_H
     6	
     7	#include<stdio.h>
     8	
     9	#define SIZE 10
    10	
    11	typedef int LIST; //把int当作List类型，实际中可以使用其它的类型或者自己定义一个List类型，不过不能是使用struct复合类型
    12	
    13	int ListSize = 0;  //定义List的实际长度，它不能比SIZE大，因为实际只有SIZE个空间
    14	
    15	//声明函数原型，这里有插入，删除，查找链表元素的函数，以及遍历链表的函数
    16	int ListInsert(LIST *list,LIST a);
    17	int ListDelete(LIST *list,LIST a);
    18	int ListTravel(LIST *list);
    19	int ListFindElement(LIST *list,LIST a);
    20	
    21	#endif /*SINGLE_LIST_H*/

 ```
 ```
     1	/* **************************
     2	 * Source file of Single List
     3	 * *************************/
     4	#include"Ex010_SingleList.h"
     5	
     6	//函数的实现，和主函数放到了一个源文件中，实际中最好不要放在一起
     7	int ListTravel(LIST *list)
     8	{
     9		int index =0;
    10	
    11		if(NULL == list)
    12			return 1;
    13	
    14		for(index=0; index<ListSize && index < SIZE; ++index)
    15			printf("%d ",list[index]);
    16	
    17		printf("\n");
    18	
    19		return 0;
    20	}
    21	
    22	//查找到元素后返回无数在链表中的位置，即数组的下标，否则返回-1
    23	int ListFindElement(LIST *list,LIST a)
    24	{
    25		int index = 0;
    26	
    27		if(NULL == list)
    28			return -1;
    29	
    30		for(index=0; index<ListSize && index < SIZE; ++index)
    31		{
    32			if(list[index] == a )
    33				return index;
    34		}
    35	
    36		return -1;
    37	}
    38	
    39	int ListInsert(LIST *list,LIST a)
    40	{
    41		if(NULL == list)
    42			return 1;
    43	
    44		if( ListSize >= SIZE)
    45		{
    46			printf("The list is full \n");
    47			return 1;
    48		}
    49	
    50		list[ListSize++] = a; //从List尾部插入元素
    51	
    52		return 0;
    53	}
    54	
    55	int ListDelete(LIST *list,LIST a)
    56	{
    57		int index = 0;
    58	
    59		if(NULL == list)
    60			return 1;
    61	
    62		if( ListSize < 0 )
    63		{
    64			printf("The list is empty\n");
    65			return 1;
    66		}
    67	
    68		index = ListFindElement(list,a);
    69	
    70		if(-1 != index )
    71		{
    72			if(index == SIZE-1) //链表中最后一个元素的时候这样删除
    73			{
    74				list[index] = 0;
    75				ListSize -= 1;
    76				return 0;
    77			}
    78			
    79			index += 1;
    80			while(index <= ListSize )
    81			{
    82				list[index-1] = list[index];
    83				index++;
    84			}
    85			list[index-1] = 0;
    86			ListSize -= 1;
    87		}
    88	
    89		return 0;
    90	}
    91	
    92	//程序主要逻辑部分
    93	int main()
    94	{
    95		int i = 0;
    96		LIST List[SIZE] = {0}; //定义了一个SIZE大小的链表，通过数组实现顺序存储
    97	
    98		for(i=0; i<SIZE; ++i)
    99			ListInsert(List,i+1);
   100	
   101		ListTravel(List);
   102		ListInsert(List,23); //注意插入的元素类型需要是LIST类型，因为当前的LIST是int类型，所以插入一个数字23
   103		ListDelete(List,10); //删除元素的类型和插入的一样，不多说了
   104		ListTravel(List);
   105		ListDelete(List,5);
   106		ListTravel(List);
   107		ListDelete(List,1);
   108		ListTravel(List);
   109	
   110	
   111		return 0;
   112	}

 ```
 各位看官，关于单链表的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 

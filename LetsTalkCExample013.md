# 一起talk C栗子吧（第十三回：C语言实例--单链表二）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是链表以及单链表顺序储存方式的例子，这一回咱们继续说单链表的例子，不
过这一回咱们说的是：单链表链式存储。

看官们单链表的链式存储，咱们在上一回已经说过，这里就不再多说了。这一回主要举例子，通过例子来
说明什么是单链表的链式存储。

通过对比单链表的顺序储存和链式存储，可以看出来。顺序存储链表的优点：遍历链表方便，查找也方便。
其缺点：删除，插入元素比较繁琐。链式存储链表的优点：插入，删除元素比较方便，遍历和查找比较繁
琐。总体来说链式存储的链表在实际开发中使用较多，因为它比较灵活，而且链表的大小可以依据需要动
态地调整，空间利用率高。

看官们，详细的代码如下，请大家参考。关于代码有以下几点需要大家注意：

- 1.在代码中创建链表时，使用头结点，这样方便链表操作。详细的原因，可以看代码中的注释。
- 2.代码中有debgu语句，在代码中如果定义DEBUG宏后，可以打印一些debug语句，这样可以快速的查找
问题的原因。如果不需要debug可以不定义这个宏，默认情况下也没有定义该宏。
- 3.代码中使用了二级指针，使用的时候特别小心。
```
     1	/* **************************
     2	 * Head file of List
     3	 * *************************/
     4	#ifndef LIST_H
     5	#define LIST_H
     6	
     7	#include<stdio.h>
     8	#include<stdlib.h>
     9	
    10	//#define DEBUG 0
    11	#ifdef DEBUG
    12	int size = 0;
    13	#endif
    14	
    15	#define SUCCESS 0
    16	#define FAILE 1
    17	
    18	typedef int ListElmt; //把int当作List类型，实际中可以使用其它的类型或者自己定义一个List类型，不过不能是使用struct复合类型
    19	typedef struct _ListNode  //List node 类型
    20	{
    21		ListElmt data;
    22		struct _ListNode *next;
    23	}ListNode;
    24	
    25	//typedef struct _ListNode ListNode;
    26	typedef struct _ListNode *List; //定义链表的类型为ListNode类型的指针
    27	
    28	//声明函数原型，这里有插入，删除，查找链表元素的函数，以及遍历链表的函数
    29	int ListCreate(List *list,int len);
    30	int ListDestroy(List *list);
    31	int ListInsert(List *list,ListNode *node);
    32	int ListDelete(List *list,ListElmt data);
    33	int ListTravel(List list);
    34	int ListFindElement(List list,ListElmt data);
    35	
    36	#endif /*LIST_H*/
```

```
     1	/* **************************
     2	 * Soure file of List
     3	 * *************************/
     4	
     5	#include"Ex011_List.h"
     6	
     7	//实现List的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	
     9	//创建List Node,创建一个长度为len的链表，其中有一个链表头，链表中结点个数为len
    10	int ListCreate(List *list,int len)
    11	{
    12		ListNode *l = NULL;
    13		ListNode *p = NULL;
    14	
    15		l = (ListNode*)malloc(sizeof(ListNode)); //先创建头结点
    16	
    17		if(NULL == l) //分配成功后才能对它进行操作
    18			return FAILE;
    19	
    20		*list = l; //创建头结点,并且初始化
    21		l->data = 0;
    22		l->next = NULL;
    23	#ifdef DEBUG
    24		size += 1;
    25	#endif
    26	
    27		while(len-- > 0 )
    28		{
    29			p = (ListNode*)malloc(sizeof(ListNode)); //新创建结点
    30	
    31			if(NULL != p)
    32			{
    33				l->next = p;
    34				l = p;
    35				l->data = 0; //结点中的元素初始化为0，这里的data是Int类型
    36				l->next = NULL;
    37			}
    38	#ifdef DEBUG
    39		size += 1;
    40	#endif
    41		}
    42	
    43		return SUCCESS;
    44	}
    45	
    46	//删除List,从链表头开始删除,每次删除一个结点,直到所有结点都删除为止，此时为空链表,只剩下头结点
    47	int ListDestroy(List *list)
    48	{
    49		ListNode *l = NULL;
    50		ListNode *p = NULL;
    51	
    52		if(NULL == *list) //空链表时不进行删除操作
    53		{
    54			printf("the list is empty \n");
    55			return FAILE;
    56		}
    57	
    58		l = (*list)->next;
    59		free(*list); //释放头结点
    60		*list = NULL;
    61	
    62	#ifdef DEBUG
    63		size -= 1;
    64		printf(" a delete a node in the list \n");
    65	#endif
    66		while(l != NULL)  //从链表头结点的下一个结点开始,一个结点接着一个结点地删除
    67		{
    68			p = l->next;
    69			free(l);
    70			l = p;
    71	#ifdef DEBUG
    72		size -= 1;
    73		printf("delete a node in the list \n");
    74	#endif
    75		}
    76	
    77		return SUCCESS;
    78	}
    79	
    80	//向链表中插入结点，插入时从链表尾部插入，每次插入一个结点.
    81	int ListInsert(List *list,ListNode *node)
    82	{
    83		ListNode *l = NULL;
    84	
    85		if(NULL == *list)
    86		{
    87			printf("this is a empty list, can't be insered \n");
    88			return FAILE;
    89		}
    90	
    91		l = (*list)->next;
    92	//	while(l != NULL) //遍历链表到表尾
    93	//		l = l->next;
    94	
    95	//	l = node; //在表尾插入结点
    96	//	l->next = NULL;
    97	
    98		(*list)->next = node; //在表头，也就是头结点后面插入结点，省去遍历链表的时间，这是有头结点的好处
    99		node->next = l;
   100	
   101	#ifdef DEBUG
   102		size += 1;
   103	#endif
   104		return SUCCESS;
   105	}
   106	
   107	//删除链表中包含data的结点
   108	int ListDelete(List *list,ListElmt data)
   109	{
   110		int flag = 0;
   111		int result = FAILE;
   112		ListNode  *current = NULL;
   113		ListNode *next = NULL;
   114	
   115		if(NULL == *list) //空链表没有结点，不能删除结点
   116		{
   117			printf("this is a empty list, can't be deleted \n");
   118			return FAILE;
   119		}
   120	
   121		current = *list;
   122		next = (*list)->next;
   123	
   124		while(next != NULL) //依次遍历链表，查找被删除的元素，如果找到则删除结点，并且停止遍历链表
   125		{
   126			if(data == next->data)
   127			{
   128				current->next = next->next;
   129				free(next);
   130				next = NULL;
   131				flag = 1;
   132	#ifdef DEBUG
   133		size -= 1;
   134	#endif
   135				break;
   136			}
   137			current = next;
   138			next = next->next;
   139		}
   140	
   141		if( 1 == flag )
   142			result = SUCCESS;
   143		else
   144			result =  FAILE;
   145	
   146		return result;
   147	}
   148	
   149	//遍历链表，显示链表中的每个结点的data
   150	int ListTravel(List list)
   151	{
   152		ListNode *l = NULL;
   153	
   154		if(NULL == list) //空链表直接返回
   155		{
   156			printf("It is a empyt list \n");
   157			return FAILE;
   158		}
   159	
   160		l = list->next;
   161	
   162		while(NULL != l) //遍历链表，并且显示链表中的data
   163		{
   164			printf("%d \n",l->data);
   165			l = l->next;
   166		}
   167	
   168	#ifdef DEBUG
   169		printf("list size: %d \n",size);
   170	#endif
   171		return SUCCESS;
   172	}
   173	
   174	//查找链表中是否包含值为data的结点
   175	int ListFindElement(List list,ListElmt data)
   176	{
   177		ListNode *l = NULL;
   178		int result = FAILE;
   179	
   180		if(NULL == list) //空链表直接返回
   181		{
   182			printf("It is a empyt list \n");
   183			return FAILE;
   184		}
   185	
   186		l = list->next;
   187		while(NULL != l) //依次遍历链表，查找值为data的结点
   188		{
   189			if(data == l->data) //找到后停止遍历链表,否则继续遍历链表
   190			{
   191				result = SUCCESS;
   192				break;
   193			}
   194			else
   195				l = l->next;
   196		}
   197	
   198		return result;
   199	}
   200	
   201	int main()
   202	{
   203		int result  = FAILE;
   204		int len = 3;
   205		ListNode *node = NULL; //node必须是指针，而且要用malloc分配空间，因为要使free释放
   206		List list = NULL; //创建一个指向链表的空指针
   207	
   208		node = (ListNode *)malloc(sizeof(ListNode));
   209		if(NULL != node)
   210		{
   211			node->data = 1;
   212			node->next = NULL;
   213		}
   214	
   215		result = ListCreate(&list,len); //创建一个长度为Len的链表
   216		if(result == SUCCESS)
   217			ListTravel(list);
   218	
   219		printf("Insert a node into list \n");
   220		ListInsert(&list,node);
   221		ListTravel(list);
   222		
   223		result = ListFindElement(list,0);
   224		if(result == SUCCESS )
   225			printf("find it in the list \n");
   226		else
   227			printf("don't find it in the list \n");
   228	
   229		printf("main delete a node in list \n");
   230		result = ListDelete(&list,1);
   231		if(result == SUCCESS )
   232			ListTravel(list);
   233	
   234		ListDestroy(&list);
   235	
   236	#ifdef DEBUG
   237		printf("list size: %d \n",size);
   238	#endif
   239		ListTravel(list);
   240		return result;
   241	}
```

各位看官，关于单链表链式存储的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

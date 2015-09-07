# 一起talk C栗子吧（第十四回：C语言实例--循环链表）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是单链表链式存储的例子，这一回咱们说的例子是：循环链表。

看官们，循环链表也是链表的一种，只不过该链表的头部和尾部相连接，所以构成了一个循环链，因此叫
作循环链表。让我们一起对比一下单链接与循环链表的不同之处：单链表的尾结点哪里也没有指，因为它
的next指针值为空。循环链表的尾结点指向了它的头结点。

看官们，详细的代码放如下，大家可以参考。该例子的代码与上一回中例子中的代码类似，不同之处在于，
上一回的例子中判断链表结束时需要使用指针和NULL进行对比。这一回的例子中判断链表结束时需要使用
尾结点的指针和头结点的指针进行对比。如果这两个指针相同，那么就表示链表结束。

```
     1	/* **************************
     2	 * Head file of CircleList
     3	 * *************************/
     4	#ifndef CIRCLE_LIST_H
     5	#define CIRCLE_LIST_H
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
    36	#endif /*CIRCLE_LIST_H*/
```

```
     1	/* **************************
     2	 * Soure file of Cirecle List
     3	 * *************************/
     4	
     5	#include"CircleList.h"
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
    22		l->next = l; //循环链表，首尾相连
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
    33				p->next = l->next;
    34				l->next = p;
    35				l = p;
    36				l->data = 0; //结点中的元素初始化为0，这里的data是Int类型
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
    59	#ifdef DEBUG
    60		size -= 1;
    61		printf(" a delete a node in the list \n");
    62	#endif
    63		while(l != *list)  //从链表头结点的下一个结点开始,一个结点接着一个结点地删除
    64		{
    65			p = l->next;
    66			free(l);
    67			l = p;
    68	#ifdef DEBUG
    69		size -= 1;
    70		printf("delete a node in the list \n");
    71	#endif
    72		}
    73		free(*list); //释放头结点
    74		*list = NULL;
    75	
    76		return SUCCESS;
    77	}
    78	
    79	//向链表中插入结点，插入时从链表尾部插入，每次插入一个结点.
    80	int ListInsert(List *list,ListNode *node)
    81	{
    82		ListNode *l = NULL;
    83	
    84		if(NULL == *list)
    85		{
    86			printf("this is a empty list, can't be insered \n");
    87			return FAILE;
    88		}
    89	
    90		l = (*list)->next;
    91	//	while(l != *list) //遍历链表到表尾
    92	//		l = l->next;
    93	
    94	//	l = node; //在表尾插入结点
    95	//	l->next =*list;
    96	
    97		(*list)->next = node; //在表头，也就是头结点后面插入结点，省去遍历链表的时间，这是有头结点的好处
    98		node->next = l;
    99	
   100	#ifdef DEBUG
   101		size += 1;
   102	#endif
   103		return SUCCESS;
   104	}
   105	
   106	//删除链表中包含data的结点
   107	int ListDelete(List *list,ListElmt data)
   108	{
   109		int flag = 0;
   110		int result = FAILE;
   111		ListNode  *current = NULL;
   112		ListNode *next = NULL;
   113	
   114		if(NULL == *list) //空链表没有结点，不能删除结点
   115		{
   116			printf("this is a empty list, can't be deleted \n");
   117			return FAILE;
   118		}
   119	
   120		current = *list;
   121		next = (*list)->next;
   122	
   123		while(next != current) //依次遍历链表，查找被删除的元素，如果找到则删除结点，并且停止遍历链表
   124		{
   125			if(data == next->data)
   126			{
   127				current->next = next->next;
   128				free(next);
   129				next = NULL;
   130				flag = 1;
   131	#ifdef DEBUG
   132		size -= 1;
   133	#endif
   134				break;
   135			}
   136			current = next;
   137			next = next->next;
   138		}
   139	
   140		if( 1 == flag )
   141			result = SUCCESS;
   142		else
   143			result =  FAILE;
   144	
   145		return result;
   146	}
   147	
   148	//遍历链表，显示链表中的每个结点的data
   149	int ListTravel(List list)
   150	{
   151		ListNode *l = NULL;
   152	
   153		if(NULL == list) //空链表直接返回
   154		{
   155			printf("It is a empyt list \n");
   156			return FAILE;
   157		}
   158	
   159		l = list->next;
   160	
   161		while(list != l) //遍历链表，并且显示链表中的data
   162		{
   163			printf("%d \n",l->data);
   164			l = l->next;
   165		}
   166	
   167	#ifdef DEBUG
   168		printf("list size: %d \n",size);
   169	#endif
   170		return SUCCESS;
   171	}
   172	
   173	//查找链表中是否包含值为data的结点
   174	int ListFindElement(List list,ListElmt data)
   175	{
   176		ListNode *l = NULL;
   177		int result = FAILE;
   178	
   179		if(NULL == list) //空链表直接返回
   180		{
   181			printf("It is a empyt list \n");
   182			return FAILE;
   183		}
   184	
   185		l = list->next;
   186		while(list != l) //依次遍历链表，查找值为data的结点
   187		{
   188			if(data == l->data) //找到后停止遍历链表,否则继续遍历链表
   189			{
   190				result = SUCCESS;
   191				break;
   192			}
   193			else
   194				l = l->next;
   195		}
   196	
   197		return result;
   198	}
   199	
   200	int main()
   201	{
   202		int result  = FAILE;
   203		int len = 3;
   204		ListNode *node = NULL; //node必须是指针，而且要用malloc分配空间，因为要使free释放
   205		List list = NULL; //创建一个指向链表的空指针
   206	
   207		node = (ListNode *)malloc(sizeof(ListNode));
   208		if(NULL != node)
   209		{
   210			node->data = 1;
   211			node->next = NULL;
   212		}
   213	
   214		result = ListCreate(&list,len); //创建一个长度为Len的链表
   215		if(result == SUCCESS)
   216			ListTravel(list);
   217	
   218		printf("Insert a node into list \n");
   219		ListInsert(&list,node);
   220		ListTravel(list);
   221		
   222		result = ListFindElement(list,0);
   223		if(result == SUCCESS )
   224			printf("find it in the list \n");
   225		else
   226			printf("don't find it in the list \n");
   227	
   228		printf("main delete a node in list \n");
   229		result = ListDelete(&list,0);
   230		if(result == SUCCESS )
   231			ListTravel(list);
   232	
   233		ListDestroy(&list);
   234	
   235	#ifdef DEBUG
   236		printf("list size: %d \n",size);
   237	#endif
   238		ListTravel(list);
   239		return result;
   240	}
```

各位看官，关于循环列表的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。


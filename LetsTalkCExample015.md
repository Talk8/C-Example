# 一起talk C栗子吧（第十五回：C语言实例--双向链表）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是循环链表的例子，这一回咱们说的例子是：双向链表。

看官们，双向链表也是一种链表。我们在前面两回中说到的链表，都是沿着链表头部到链表尾部这样的方
向进行操作，而今天咱们要说的双向链表既可以沿着链表头部到链表尾部这样的方向进行操作，也可以沿
着链表尾部到链表头部这样的方向进行操作。这也是正是叫它双向链表的原因。

在例子中，查找和删除结点的函数中，可以使用沿着链表尾部向链表头部这样的方向进行查找或者删除，
当然了，也可以向单链表一样沿着链表头部到链表尾部这样的方向进行查找或者删除。不论沿着哪个方向
操作，只需要关注该方向的指针就可以。比如，沿着链表头部到链表尾部这样的方向进行相关的操作，只
需要关注结点中的next指针就行，pre指针可以忽略。但是删除操作需要注意，因为它会从链表中删除一
个符合要求的结点，删除的时候需要把该结点的pre和next指针都处理好，不然会破坏链表的完成性，在
删除操作后，如果再进行遍历操作，就会因为链表不完整，遍历不到链表中的所有结点，也就是形成了断
链，这是最严重的错误。我在代码中有中文注释。

看官们，详细的代码如下，大家可以参考：
```
     1	/* **************************
     2	 * Head file of Double Linked List
     3	 * *************************/
     4	#ifndef DOUBLE_LINKED_LIST_H
     5	#define DOUBLE_LINKED_LIST_H
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
    22		struct _ListNode *pre;
    23		struct _ListNode *next;
    24	}ListNode;
    25	
    26	//typedef struct _ListNode ListNode;
    27	typedef struct _ListNode *List; //定义链表的类型为ListNode类型的指针
    28	
    29	//声明函数原型，这里有插入，删除，查找链表元素的函数，以及遍历链表的函数
    30	int ListCreate(List *list,int len);
    31	int ListDestroy(List *list);
    32	int ListInsert(List *list,ListNode *node);
    33	int ListDelete(List *list,ListElmt data);
    34	int ListTravel(List list);
    35	int ListFindElement(List list,ListElmt data);
    36	
    37	#endif /*DOUBLE_LINKED_LIST_H*/
```

```
     1	/* **************************
     2	 * Soure file of Double Linked List
     3	 * *************************/
     4	
     5	#include"DoubleLinkedList.h"
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
    22		l->pre = NULL;
    23		l->next = NULL;
    24	#ifdef DEBUG
    25		size += 1;
    26	#endif
    27	
    28		while(len-- > 0 )
    29		{
    30			p = (ListNode*)malloc(sizeof(ListNode)); //新创建结点
    31	
    32			if(NULL != p)
    33			{
    34				l->next = p;
    35				p->pre = l;
    36				p->next = NULL;
    37				l = p;
    38				l->data = 0; //结点中的元素初始化为0，这里的data是Int类型
    39			}
    40	#ifdef DEBUG
    41		size += 1;
    42	#endif
    43		}
    44	
    45		return SUCCESS;
    46	}
    47	
    48	//删除List,从链表头开始删除,每次删除一个结点,直到所有结点都删除为止，此时为空链表,只剩下头结点
    49	int ListDestroy(List *list)
    50	{
    51		ListNode *l = NULL;
    52		ListNode *p = NULL;
    53	
    54		if(NULL == *list) //空链表时不进行删除操作
    55		{
    56			printf("the list is empty \n");
    57			return FAILE;
    58		}
    59	
    60		l = (*list)->next;
    61		free(*list); //释放头结点
    62		*list = NULL;
    63	
    64	#ifdef DEBUG
    65		size -= 1;
    66		printf(" a delete a node in the list \n");
    67	#endif
    68		while(NULL != l)  //从链表头结点的下一个结点开始,一个结点接着一个结点地删除
    69		{
    70			p = l->next; //detroy循环链表，沿着一个方向遍历就行，不需要考虑pre,但是delete链表时需要考虑,因为只是删除链表中的一个结点，不考虑会影响链表的完成性。
    71			free(l);
    72			l = p;
    73	#ifdef DEBUG
    74		size -= 1;
    75		printf("delete a node in the list \n");
    76	#endif
    77		}
    78		return SUCCESS;
    79	}
    80	
    81	//向链表中插入结点，插入时从链表尾部插入，每次插入一个结点.
    82	int ListInsert(List *list,ListNode *node)
    83	{
    84		ListNode *l = NULL;
    85	
    86		if(NULL == *list)
    87		{
    88			printf("this is a empty list, can't be insered \n");
    89			return FAILE;
    90		}
    91	
    92		l = (*list)->next;
    93	//	while(l != *list) //遍历链表到表尾
    94	//		l = l->next;
    95	
    96	//	l = node; //在表尾插入结点
    97	//	l->next =*list;
    98	
    99		(*list)->next = node; //在表头，也就是头结点后面插入结点，省去遍历链表的时间，这是有头结点的好处
   100		node->pre = l->pre;
   101		l->pre = node;
   102		node->next = l;
   103	
   104	#ifdef DEBUG
   105		size += 1;
   106	#endif
   107		return SUCCESS;
   108	}
   109	
   110	//删除链表中包含data的结点
   111	int ListDelete(List *list,ListElmt data)
   112	{
   113		int flag = 0;
   114		int result = FAILE;
   115		ListNode  *current = NULL;
   116		ListNode *next = NULL;
   117	
   118		if(NULL == *list) //空链表没有结点，不能删除结点
   119		{
   120			printf("this is a empty list, can't be deleted \n");
   121			return FAILE;
   122		}
   123	
   124		current = *list;
   125		next = (*list)->next;
   126	
   127		while(NULL != next) //依次遍历链表，查找被删除的元素，如果找到则删除结点，并且停止遍历链表
   128		{
   129			if(data == next->data)
   130			{
   131				current->next = next->next;
   132				(next->next)->pre = next->pre;
   133				free(next);
   134				next = NULL;
   135				flag = 1;
   136	#ifdef DEBUG
   137		size -= 1;
   138	#endif
   139				break;
   140			}
   141			current = next; //这里只沿一个方向进行遍历就可以
   142			next = next->next;
   143		}
   144	
   145		if( 1 == flag )
   146			result = SUCCESS;
   147		else
   148			result =  FAILE;
   149	
   150		return result;
   151	}
   152	
   153	//遍历链表，显示链表中的每个结点的data
   154	int ListTravel(List list)
   155	{
   156		ListNode *l = NULL;
   157	
   158		if(NULL == list) //空链表直接返回
   159		{
   160			printf("It is a empyt list \n");
   161			return FAILE;
   162		}
   163	
   164		l = list->next;
   165	
   166		while(l != NULL) //遍历链表，并且显示链表中的data
   167		{
   168			printf("%d \n",l->data);
   169			l = l->next;
   170		}
   171	
   172	#ifdef DEBUG
   173		printf("list size: %d \n",size);
   174	#endif
   175		return SUCCESS;
   176	}
   177	
   178	//查找链表中是否包含值为data的结点
   179	int ListFindElement(List list,ListElmt data)
   180	{
   181		ListNode *l = NULL;
   182		int result = FAILE;
   183	
   184		if(NULL == list) //空链表直接返回
   185		{
   186			printf("It is a empyt list \n");
   187			return FAILE;
   188		}
   189	
   190		l = list->next;
   191		while( NULL != l) //依次遍历链表，查找值为data的结点
   192		{
   193			if(data == l->data) //找到后停止遍历链表,否则继续遍历链表
   194			{
   195				result = SUCCESS;
   196				break;
   197			}
   198			else
   199				l = l->next;
   200		}
   201	
   202		return result;
   203	}
   204	
   205	int main()
   206	{
   207		int result  = FAILE;
   208		int len = 3;
   209		ListNode *node = NULL; //node必须是指针，而且要用malloc分配空间，因为要使free释放
   210		List list = NULL; //创建一个指向链表的空指针
   211	
   212		node = (ListNode *)malloc(sizeof(ListNode));
   213		if(NULL != node)
   214		{
   215			node->data = 1;
   216			node->next = NULL;
   217			node->pre = NULL;
   218		}
   219	
   220		result = ListCreate(&list,len); //创建一个长度为Len的链表
   221		if(result == SUCCESS)
   222			ListTravel(list);
   223	
   224		printf("Insert a node into list \n");
   225		ListInsert(&list,node);
   226		ListTravel(list);
   227		
   228		result = ListFindElement(list,0);
   229		if(result == SUCCESS )
   230			printf("find it in the list \n");
   231		else
   232			printf("don't find it in the list \n");
   233	
   234		printf("main delete a node in list \n");
   235		result = ListDelete(&list,0);
   236		if(result == SUCCESS )
   237			ListTravel(list);
   238	
   239		ListDestroy(&list);
   240	
   241	#ifdef DEBUG
   242		printf("list size: %d \n",size);
   243	#endif
   244		ListTravel(list);
   245		return result;
   246	}
```

各位看官，关于双向链表的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

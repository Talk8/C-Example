##一起talk C栗子吧（第二十六回：C语言实例--冒泡排序）

各位看官们，大家好，上一回中咱们说的是二分查找的例子，这一回咱们说的例子是：冒泡排序。闲话休提，言归正转。让我们一起talk C栗子吧！ 

我们先来说说什么是排序，所谓的排序就是把容器中的元素依据一定的规则进行排列。我们还是像以前一样举个日常生活中的例子来说明：现在学校里基本上都在搞军训，我想大家也参加过军训，在军训前肯定
会让大家排队，教官会让大家依据自己的身高从低到高进行排队，这样排出来的队列比较整齐。在排队的过程中就使用了排序，参加军训的学生就是容器中元素，排序的规则就是教官定的：依据身高从低到高进
行排队。排序的结果就是一个整齐的军训队伍。我这么说，大家明白了吗？哪个“依据身高从低到高进行排队”是怎么进行的？台下有看官在提问了，看官莫急，你问的问题就是咱们今天要说的内容，在编写程序的
时候有多种方法可以进行排序，咱们首先讲其中的一种：冒泡排序。

冒泡排序的基本原理为：依次比较容器中相邻的两个元素，如果这两个元素不符合排序的规则，那么交换
这两个元素在容器中的位置，直到窗口中所有相邻的元素都符合排序规则为止。
冒泡排序的实现步骤如下：
- 1.从容器头部到尾部遍历容器，遍历过程中取出相邻的两个元素进行比较；
- 2.如果这两个元素不符合排序的规则，那么交换这两个元素在容器中的位置；
- 3.如果这两个元素符合排序的规则，那么回到步骤1；
- 4.反复进行步骤1到步骤3,直到遍历完容器中所有的元素为止。

看官们，详细的代码如下所示，大家可以参考。冒泡排序的优点就是简单易懂，而且容易实现。缺点就是性能相对较低。我在代码中对冒泡排序进行了优化，这样可
以提高冒泡排序的性能。
```
     1	/* **************************
     2	 * Source file of Bubble Sort
     3	 * *************************/
     4	
     5	#include<stdio.h>
     6	#include<stdlib.h>
     7	
     8	#define SUCCESS 0
     9	#define FAILE 1
    10	
    11	#define SIZE 10 //容器大小定义为10
    12	
    13	typedef int Elmt; //把int当作容器中元素的类型，实际中可以使用其它的类型或者自己定义一个元素类型
    14	
    15	//冒泡排序函数,头文件的内容比较简单，因此把头文件和源文件放在一起
    16	int BubbleSort(Elmt* a,int size)
    17	{
    18		int i,j,temp,flag;
    19		i = j = temp = 0;
    20	
    21		if(NULL == a)
    22			return FAILE;
    23	
    24		flag = 1;
    25		for(i=0; i<size && flag; ++i)
    26		{
    27	
    28			flag = 0;//通过加入标记来优化，如果已经符合规则了，就停止遍历
    29	
    30			for(j=size-1; j>=i; --j)
    31			{
    32				if(*(a+j) < *(a+j-1))
    33				{
    34					temp = *(a+j);
    35					*(a+j) = *(a+j-1);
    36					*(a+j-1) = temp;
    37					flag = 1;
    38				}
    39			}
    40		}
    41	
    42		return SUCCESS;
    43	}
    44	
    45	int SetInit(Elmt* a,int size)
    46	{
    47		int i =0;
    48	
    49		if(NULL == a)
    50			return FAILE;
    51	
    52		srand(time(NULL));
    53		while(i++ < size) //使用随机数初始化容器
    54			*(a+i-1) = rand()%100;
    55	
    56		return SUCCESS;
    57	}
    58	
    59	int SetShow(Elmt* a,int size)
    60	{
    61		int i =0;
    62	
    63		if(NULL == a)
    64			return FAILE;
    65	
    66		while(i++ < size)
    67			printf("%d ",*(a+i-1));
    68	
    69		printf(" \n");
    70		return SUCCESS;
    71	}
    72	
    73	int main()
    74	{
    75		int i= 0;
    76		Elmt array[SIZE] = {0}; //简单起见，使用数组做为容器
    77	
    78		SetInit(array,SIZE);
    79	
    80		printf("the elmt of array is : \n ");
    81		SetShow(array,SIZE);
    82	
    83		printf("after sort, the elmt of array is : \n ");
    84		if(!BubbleSort(array,SIZE))
    85			SetShow(array,SIZE);
    86		else
    87			printf("it is wrong \n");
    88	
    89		return SUCCESS;
    90	}
```
各位看官，关于冒泡排序的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

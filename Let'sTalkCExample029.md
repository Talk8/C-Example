##一起talk C栗子吧（第二十九回：C语言实例--选择排序）

各位看官们，大家好，上一回中咱们说的是希尔排序的例子，这一回咱们说的例子是：选择排序。闲话休提，言归正转。让我们一起talk C栗子吧！ 

选择排序的原理是：从容器中选择一个最大或者最小的元素，把该元素放到新的容器中，等到容器中的所有元素都被选择完后，新容器中存放的元素就是有序的。

在实现选择排序时，我通过交换元素的位置，充分利用了容器的空间，而没有创建新的容器，这样可以节省程序的存储空间。选择排序的实现步骤如下：

- 1.先实现一个可以从容器中找到最大元素或最小元素的函数，找到后返回该元素在容器中的位置；
- 2.首先把容器头部元素当作最大或者最小元素；
- 3.从容器的第二个元素开始，依次遍历容器；
- 4.在遍历过程中使用步骤1中的函数，找到最大元素或者最小元素所在的位置；
- 5.比较第步骤2和步骤4中两个元素的大小，如果符合排序规则，那么回到步骤2；
- 6.比较第步骤2和步骤4中两个元素的大小，如果不符合排序规则，交换这两个元素的值；
- 7.反复执行步骤2到步骤6,直到容器的尾部为止。

看官们，详细的代码如下，请大家参考使用：


```
     1	/* **************************
     2	 * Source file of Select Sort
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
    15	int findMin(Elmt *a,int start,int end)
    16	{
    17		int i,min,res;
    18	
    19		min = *(a+start);
    20		res = start;
    21	
    22		for(i=start+1; i<end; ++i)
    23		{
    24			if(min > *(a+i))
    25			{
    26				min = *(a+i);
    27				res = i;
    28			}
    29		}
    30	
    31		return res;
    32	}
    33	
    34	//选择排序函数,头文件的内容比较简单，因此把头文件和源文件放在一起
    35	int SelectSort(Elmt* a,int size)
    36	{
    37		int i,j,k,temp;
    38		i = j = temp = 0;
    39	
    40		if(NULL == a)
    41			return FAILE;
    42	
    43		for(i=1,k=0; i<size; ++i)
    44		{
    45			k = findMin(a,i,size);
    46	
    47			if(*(a+i-1) > *(a+k))
    48			{
    49				temp = *(a+i-1);
    50				*(a+i-1)= *(a+k);
    51				*(a+k)= temp;
    52			}
    53	//去掉注释，可以显示每次排序的结果
    54	/*		for(j=0; j<size; ++j)
    55				printf("%2d ",*(a+j));
    56			printf("\n");*/
    57		}
    58	
    59		return SUCCESS;
    60	}
    61	
    62	int SetInit(Elmt* a,int size)
    63	{
    64		int i =0;
    65	
    66		if(NULL == a)
    67			return FAILE;
    68	
    69		srand(time(NULL));
    70		while(i++ < size) //使用随机数初始化容器
    71			*(a+i-1) = rand()%100;
    72	
    73		return SUCCESS;
    74	}
    75	
    76	int SetShow(Elmt* a,int size)
    77	{
    78		int i =0;
    79	
    80		if(NULL == a)
    81			return FAILE;
    82	
    83		while(i++ < size)
    84			printf("%d ",*(a+i-1));
    85	
    86		printf(" \n");
    87		return SUCCESS;
    88	}
    89	
    90	int main()
    91	{
    92		int i= 0;
    93		Elmt array[SIZE] = {0}; //简单起见，使用数组做为容器
    94	
    95		SetInit(array,SIZE);
    96	
    97		printf("the elmt of array is : \n ");
    98		SetShow(array,SIZE);
    99	
   100		printf("after sort, the elmt of array is : \n ");
   101		if(!SelectSort(array,SIZE))
   102			SetShow(array,SIZE);
   103		else
   104			printf("it is wrong \n");
   105	
   106		return SUCCESS;
   107	}
```
各位看官，关于选择排序的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

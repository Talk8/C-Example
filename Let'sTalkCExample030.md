##一起talk C栗子吧（第三十回：C语言实例--快速排序）

各位看官们，大家好，上一回中咱们说的是选择排序的例子，这一回咱们说的例子是：快速排序。闲话休提，言归正转。让我们一起talk C栗子吧！ 

快速排序的原理：选定一个关键字，使容器分为两部分，一部分中的任何元素都关键字大，另一部分中的任何元素都比关键字小。然后分别对这两个部分进行排序。

快速排序的实现步骤：
- 1.选定一个关键字，我在代码里直接使用容器头部元素为关键字；
- 2.从容器的尾部到头部遍历容器，直到遇见到比关键字小的元素，然后将它交换到关键点的左边；
- 3.从容器的头部到尾部遍历容器，直到遇见到比关键字大的元素，然后将它交换到关键点的右边；
- 4.反复进行步骤2和3,直到步骤2和3中在遍历过程中相遇为止；
- 5.此时，找到了容器的分界点，分界点左边的元素比关键字大，右边的元素比关键点小；
- 6.对分界点左边的元素重复步骤1到步骤5,在程序中使用递归来实现这个步骤；
- 7.对分界点右边的元素重复步骤1到步骤5,在程序中使用递归来实现这个步骤；


看官们，详细的代码如下所示，大家可以参考使用。快速排序是所有排序算法中性能最好的，这也是叫它快速排序的原因。
```
     1	/* **************************
     2	 * Source file of Quick Sort
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
    15	int Partition(Elmt *a,int low,int high )
    16	{
    17		int temp,res;
    18		int key;
    19	
    20		temp = res = 0;
    21		key = *(a+low);//使用平均值的方法求关键字
    22	
    23		while(low < high)
    24		{
    25			while(low<high && *(a+high) >= key)
    26				high--;
    27	
    28			temp = *(a+low);
    29			*(a+low) = *(a+high);
    30			*(a+high) = temp;
    31	
    32			while(low<high && *(a+low) <= key)
    33				low++;
    34	
    35			temp = *(a+high);
    36			*(a+high) = *(a+low);
    37			*(a+low) = temp;
    38		}
    39	
    40		res = low;
    41		return res;
    42	}
    43	
    44	//快速排序函数,头文件的内容比较简单，因此把头文件和源文件放在一起
    45	int QuickSort(Elmt* a,int low, int high)
    46	{
    47		int pivot = 0;
    48	
    49		if(NULL == a)
    50			return FAILE;
    51	
    52		if(low < high)
    53		{
    54			pivot = Partition(a,low,high);
    55	
    56			QuickSort(a,low,pivot-1);
    57			QuickSort(a,pivot+1,high);
    58		}
    59	
    60		return SUCCESS;
    61	}
    62	
    63	int SetInit(Elmt* a,int size)
    64	{
    65		int i =0;
    66	
    67		if(NULL == a)
    68			return FAILE;
    69	
    70		srand(time(NULL));
    71		while(i++ < size) //使用随机数初始化容器
    72			*(a+i-1) = rand()%100;
    73	
    74		return SUCCESS;
    75	}
    76	
    77	int SetShow(Elmt* a,int size)
    78	{
    79		int i =0;
    80	
    81		if(NULL == a)
    82			return FAILE;
    83	
    84		while(i++ < size)
    85			printf("%d ",*(a+i-1));
    86	
    87		printf(" \n");
    88		return SUCCESS;
    89	}
    90	
    91	int main()
    92	{
    93		int i= 0;
    94		Elmt array[SIZE] = {0}; //简单起见，使用数组做为容器
    95	
    96		SetInit(array,SIZE);
    97	
    98		printf("the elmt of array is : \n ");
    99		SetShow(array,SIZE);
   100	
   101		printf("after sort, the elmt of array is : \n ");
   102		if(!QuickSort(array,0,SIZE-1))
   103			SetShow(array,SIZE);
   104		else
   105			printf("it is wrong \n");
   106	
   107		return SUCCESS;
   108	}

```
各位看官，关于快速排序的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。


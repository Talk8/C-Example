##一起talk C栗子吧（第二十八回：C语言实例--希尔排序）

各位看官们，大家好，上一回中咱们说的是插入排序的例子，这一回咱们说的例子是：希尔排序。闲话休提，言归正转。让我们一起talk C栗子吧！ 

希尔排序是对插入排序的一种改进，它的原理：先将容器分成若干子容器，然后分别对子容器进行插入排序，当子容器全部排序完毕后，对全部元素进行一次插入排序。

**希尔排序的实现步骤：**
- 1.选取一个增量，增量的大小可以自己定义，其大小在1到容器长度之间；
- 2.以容器头部到增量位置的元素为起点，从起点到容器尾部依次遍历容器；
- 3.在步骤2中的遍历过程中，选择一个当前位置的元素，再选择相距当前位置增量个位置的元素进行比较；
- 4.如果步骤3中的两个元素符合排序规则，回到步骤2；
- 5.如果步骤3中的两个元素不符合排序规则，那么进行一次选择排序；
- 6.减小增量的值，减小多少，可以自己定义，我在程序中减小了1；
- 7.反复执行步骤2到步骤6,直到增量值等于为止。

看官们，详细的代码如下，请大家参考。

```
     1	/* **************************
     2	 * Source file of Shell Sort
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
    15	//希尔排序函数,头文件的内容比较简单，因此把头文件和源文件放在一起
    16	int ShellSort(Elmt* a,int size)
    17	{
    18		int i,j,step,temp;
    19		i = j = temp = 0;
    20	
    21		if(NULL == a)
    22			return FAILE;
    23	
    24		step = size/2;//增量的选取可以自己定义
    25	
    26		do
    27		{
    28			for(i=step; i<size ; ++i)
    29			{
    30	
    31				if(*(a+i) < *(a+i-step))
    32				{
    33					temp = *(a+i);
    34					for(j=i-step; *(a+j)> temp && j>=0; j-=step)
    35						*(a+j+step) = *(a+j);
    36	
    37					*(a+j+step) = temp;
    38				}
    39			}
    40			step--;
    41		}while(step >0);
    42	
    43		return SUCCESS;
    44	}
    45	
    46	int SetInit(Elmt* a,int size)
    47	{
    48		int i =0;
    49	
    50		if(NULL == a)
    51			return FAILE;
    52	
    53		srand(time(NULL));
    54		while(i++ < size) //使用随机数初始化容器
    55			*(a+i-1) = rand()%100;
    56	
    57		return SUCCESS;
    58	}
    59	
    60	int SetShow(Elmt* a,int size)
    61	{
    62		int i =0;
    63	
    64		if(NULL == a)
    65			return FAILE;
    66	
    67		while(i++ < size)
    68			printf("%d ",*(a+i-1));
    69	
    70		printf(" \n");
    71		return SUCCESS;
    72	}
    73	
    74	int main()
    75	{
    76		int i= 0;
    77		Elmt array[SIZE] = {0}; //简单起见，使用数组做为容器
    78	
    79		SetInit(array,SIZE);
    80	
    81		printf("the elmt of array is : \n ");
    82		SetShow(array,SIZE);
    83	
    84		printf("after sort, the elmt of array is : \n ");
    85		if(!ShellSort(array,SIZE))
    86			SetShow(array,SIZE);
    87		else
    88			printf("it is wrong \n");
    89	
    90		return SUCCESS;
    91	}

```
在希尔排序中使用了插入排序，但是它的效率比插入排序要高，这全是增量的功劳。

各位看官，关于希尔排序的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

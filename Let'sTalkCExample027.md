## 一起talk C栗子吧（第二十七回：C语言实例--插入排序）

各位看官们，大家好，上一回中咱们说的是冒泡排序的例子，这一回咱们说的例子是：插入排序。闲话休
提，言归正转。让我们一起talk C栗子吧！ 

看官们，我们这回说的插入排序和前一回说的冒泡排序一样，也是一种排序方法，只是它们的原理的不同而
已。插入排序的原理为：从容器中取出一个元素，把该元素插入已经有序的另外一个容器中，并且保持该
容器中元素原来的顺序。

**插入排序的实现步骤：**
- 1.从容器第二个元素开始到容器尾部遍历容器，遍历过程中取出当前位置的元素和该元素的前一个元素进
行比较，判断它们是否符合排序的规则；
- 2.如果这两个元素符合排序的规则，那么回到步骤1；
- 3.如果这两个元素不符合排序的规则，那么把容器头部到当前元素的位置看作一个新的容器；
- 4.查找当前元素在新容器中的位置，同时向新容器尾部移动新容器中的元素，移动一个位置就可以；
- 5.在新容器中找到当前元素的位置后，把当前元素放到该位置上；
- 6.反复进行步骤1到步骤5,直到遍历完容器中所有的元素为止。

看官们，详细的代码如下，请大家参考：
```
     1	/* **************************
     2	 * Source file of Insert Sort
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
    15	//插入排序函数,头文件的内容比较简单，因此把头文件和源文件放在一起
    16	int InsertSort(Elmt* a,int size)
    17	{
    18		int i,j,temp;
    19		i = j = temp = 0;
    20	
    21		if(NULL == a)
    22			return FAILE;
    23	
    24		for(i=1; i<size ; ++i)
    25		{
    26	
    27			if(*(a+i) < *(a+i-1))
    28			{
    29				temp = *(a+i);
    30				for(j=i-1; *(a+j)> temp && j>=0; --j)
    31					*(a+j+1) = *(a+j);
    32	
    33				*(a+j+1) = temp;
    34			}
    35		}
    36	
    37		return SUCCESS;
    38	}
    39	
    40	int SetInit(Elmt* a,int size)
    41	{
    42		int i =0;
    43	
    44		if(NULL == a)
    45			return FAILE;
    46	
    47		srand(time(NULL));
    48		while(i++ < size) //使用随机数初始化容器
    49			*(a+i-1) = rand()%100;
    50	
    51		return SUCCESS;
    52	}
    53	
    54	int SetShow(Elmt* a,int size)
    55	{
    56		int i =0;
    57	
    58		if(NULL == a)
    59			return FAILE;
    60	
    61		while(i++ < size)
    62			printf("%d ",*(a+i-1));
    63	
    64		printf(" \n");
    65		return SUCCESS;
    66	}
    67	
    68	int main()
    69	{
    70		int i= 0;
    71		Elmt array[SIZE] = {0}; //简单起见，使用数组做为容器
    72	
    73		SetInit(array,SIZE);
    74	
    75		printf("the elmt of array is : \n ");
    76		SetShow(array,SIZE);
    77	
    78		printf("after sort, the elmt of array is : \n ");
    79		if(!InsertSort(array,SIZE))
    80			SetShow(array,SIZE);
    81		else
    82			printf("it is wrong \n");
    83	
    84		return SUCCESS;
    85	}

```
各位看官，关于插入排序的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

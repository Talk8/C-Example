# 一起talk C栗子吧（第二回：C语言实例--判断闰年）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，  
言归正转。让我们一起talk C语言实例吧！   

看官们，上一回中咱们给小说做了个开头，这一回咱们正式说C例子，这回说的例子是：判断闰年。  

看官们，闰年是什么？这个是地理天文方面的概念。如果不明白的话，自己百度去，哈哈。我也偷一把懒。  
看官们，判断闰年的方法有两种：  

- 1.如果某年能被4整除，但是不能被100整除，那么这一年就是闰年。
- 2.如果某年能被400整除，那么这一年就是闰年。

看官们看到整除肯定想到除法了吧，其实C程序中的除法运算和数学中的除法运算不一样，C程序中除法运  
算只会取整数，小数点后面的小数会被舍弃。比如：5/3=1.666...。这是数学运算的结果，C程序中的结果  
是1.因为它把1后面的小数部分舍弃了。所以我们不能使用除法运算来判断闰年。哪怎么判断？看官莫急。  
在C程序中提供了取余运算，运算符号是%。取余运算就是取出除法运算中的余数。比如：5/3的余数是2.  
那么5%3的运算结果是2.大家想想，对一个数字进行取余运算后，如果运算结果为0，这代表着什么意思？  
“这表示这个数字可以被另外一个数字整除”。这位看官说的对。比如，4%2=0就可以说明4能被2整除。看  
官们，话都说到这里了，大家现在明白如何判断闰年了吧。  

看官们，详细的代码如下，共享给大家参考使用：

```
     1	/* **************************
     2	 * For Leap Year
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	#define SUCCESS 1
     7	#define FAILED  0
     8	#define BAD_PARAMETERS -1
     9	
    10	int LeapYear(int year)
    11	{
    12		int result = 0;
    13		if(year <=0 || year >9999)
    14		{
    15			printf("The year is not a correct year,(between 0 - 9999 )\n");
    16			return BAD_PARAMETERS;
    17		}
    18	
    19		if( (year % 400 == 0)
    20		||  ((year % 4 == 0) && (year % 100 != 0)) )
    21			return SUCCESS;
    22		else
    23			return FAILED;
    24	
    25	}
    26	int main()
    27	{
    28		int year, result;
    29		year = result = 0;
    30	
    31		printf("Please input a year,such as 2015 \n");
    32		scanf("%d",&year);
    33		result = LeapYear(year);
    34	
    35		if(result == SUCCESS)
    36			printf("It is a Leap Year \n");
    37		else if(result == FAILED)
    38			printf("It is not a Leap Year \n");
    39		else
    40			printf("Please check you input years \n");
    41	
    42		return 0;
    43	}    
```
各位看官，关于判断闰年的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。  

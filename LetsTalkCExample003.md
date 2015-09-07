# 一起talk C栗子吧（第三回：C语言实例--求阶乘）
 
各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C语言实例吧！  
 
看官们，上一回中咱们说的是判断闰年的例子，这一回咱们说的例子是：求阶乘。 
  
看官们，阶乘是数学中的一种运算，通常使用感叹号来表示阶乘。比如：3!表示3的阶乘。阶乘的定义是这
样的：正整数n=0时，n的阶段乘为1,n>0时，n的阶乘为n*(n-1)!。 
 
看官们，我在程序中使用了两种方法来求阶乘。一种是递归方法，另外一种是循环方法。正文中就不写代
码了，详细的代码如下，请大家参考使用： 
 
```
     1	/* **************************
     2	 * For Factorial
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	#define SUCCESS 1
     7	#define FAILED  0
     8	#define BAD_PARAMETERS -1
     9	
    10	//使用递归方法来求阶乘
    11	int Factorial(int n)
    12	{
    13		if(n < 0)
    14			return BAD_PARAMETERS;
    15	
    16		if(n == 0)
    17			return 1;
    18		else
    19			return n*Factorial(n-1);
    20	}
    21	
    22	//使用循环方法来求阶乘
    23	int f(int n)
    24	{
    25		int res = 1;
    26		int i = 0;
    27	
    28		if(n < 0)
    29			return BAD_PARAMETERS;
    30	
    31		if(n == 0)
    32			return 1;
    33	
    34		for(i=0;i<n;++i)
    35			res *= (i+1);
    36	
    37		return res;
    38	}
    39	
    40	int main()
    41	{
    42		int result = 0;
    43		
    44		result = Factorial(5);
    45		if(result > 0)
    46			printf("%d \n",result);
    47	
    48		result = f(5);
    49		if(result > 0)
    50			printf("%d \n",result);
    51	
    52		return 0;
    53	}
```

补充一点：循环和递归是比较常见的方法，所以这里不做过多的说明。不过，在工程中尽量少用递归，一
般情况下，递归可以解决的问题，可以使用循环方法去解决。不推荐递归的理由是因为，递归的性能稍微
差一些，尤其在递归的嵌套比较深的时候。 

各位看官，关于判求阶乘的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 

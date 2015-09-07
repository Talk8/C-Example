# 一起talk C栗子吧（第九回：C语言实例--最大公约数）
  
各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  
  
看官们，上一回中咱们说的是素数的例子，这一回咱们说的例子是：最大公约数。 
   
看官们，最大公约数也叫最大公因数。两个整数中的公约数有好几个，这些公约数中最大的一个就叫作最
大公约数。当然了，这是数学中的一个概念，如果不明白了，可以查阅相关的数学知识。 
  
最大公约数的求法有好几种，最常用的是**辗转相除法，也叫欧几里德算法**。该算法的原理如下：

- 如果正整数a除以正整数b所得的余数为c，那么a和b的最大公约数与b和c的最大公约数相等。
- 重复步骤1中的操作，继续求b和c的最大公约数。如此反复，直到余数等于0为止。
  
看官们，详细的代码如下，请大家参考 

 ```
     1	/* **************************
     2	 * For Greatest Common Divisor
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	int main()
     7	{
     8		int a,b,gcd,temp,ta,tb;
     9		int mod;
    10		a = b = gcd = temp = ta = tb = mod = 0;
    11	
    12		printf("Please input 2 number for get the GCD of them .\n");
    13		scanf("%d %d",&a,&b);
    14		if(a <0 || b < 0)
    15		{
    16			printf("bad input number \n");
    17			return 0;
    18		}
    19	
    20		if(a < b)
    21		{
    22			temp = a;
    23			a = b;
    24			b = temp;
    25		}
    26	
    27		ta = a;
    28		tb = b;
    29		mod= a % b;
    30		while(mod != 0)
    31		{
    32			ta = tb;
    33			tb = mod;
    34			mod = ta % tb;
    35		}
    36	
    37		printf("the GCD of %d and %d is:%d \n",a,b,tb);
    38	
    39		return 0;
    40	}
    41	
 ```
   
各位看官，关于最大公约数的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 
   

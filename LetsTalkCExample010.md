# 一起talk C栗子吧（第十回：C语言实例--最小公倍数）
   
各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  
  
看官们，上一回中咱们说的是最大公约数的例子，这一回咱们说的例子是：最小公倍数。 
   
看官们，最小公倍数和最大公约数类似。两个整数中的公倍数有好多个，这些公约数中最小的一个就叫作
**最小公倍数**。当然了，这是数学中的一个概念，如果不明白了，可以查阅相关的数学知识。 

最小公倍数的求法有好几种，最常用的是通过最大公约数来求。因为**两个数的最大公约数乘以它们的最小 
公倍数等于这两个数的积。**所以通常先求出两个数的最大公约数，然后用两个数的积除以它们的最大公约
数就得到了它们的最小公倍数。 
  
看官们，详细的代码如下，请大家参考：
 ```
     1	
     2	/* **************************
     3	 * For Least Common Multiple
     4	 * *************************/
     5	#include<stdio.h>
     6	
     7	int main()
     8	{
     9		int a,b,gcd,temp,ta,tb;
    10		int mod,res,lcm;
    11		a = b = gcd = temp = ta = tb = mod = res = lcm = 0;
    12	
    13		printf("Please input 2 number for get the LCM of them .\n");
    14		scanf("%d %d",&a,&b);
    15		if(a <0 || b < 0)
    16		{
    17			printf("bad input number \n");
    18			return 0;
    19		}
    20	
    21		if(a < b)
    22		{
    23			temp = a;
    24			a = b;
    25			b = temp;
    26		}
    27	
    28		ta = a;
    29		tb = b;
    30		mod= a % b;
    31		while(mod != 0)
    32		{
    33			ta = tb;
    34			tb = mod;
    35			mod = ta % tb;
    36		}
    37	
    38		lcm = (a * b)/tb; // a和b 积除以gcd等于lcm
    39		printf("the LCM of %d and %d is:%d \n",a,b,lcm);
    40	
    41		return 0;
    42	}
    43	
 ```

各位看官，关于最小公倍数的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 
   

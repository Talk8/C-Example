# 一起talk C栗子吧（第八回：C语言实例--素数）
  
各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  
  
看官们，上一回中咱们说的是进制转换的例子，这一回咱们说的例子是：素数。  
   
**素数又叫质数**，在大于1的自然数中，如果一个正整数除了1和它本身外，不能被其它自然数整除，那么这
个数就是一个素数。素数比较多，所以咱们例子中只展示从1到100这个范围内的素数。 
  
看官们觉得这个例子算是简单，我也觉得比较简单。只要把范围内的数从头到尾遍历一下，判断是否能被
除1和自身以外的其它的数整除就可以。我专门说素数这个例子是为想介绍另外一种方法，该方法可以节省
遍历的时间，提高程序运行效率。我在例子中使用的**原理：假如有一个正整数n，除了1和它本身外，用从2
到正整数n的平方根之间所有的正整数数去除 n，如果n都不能被整除。那么正整数n就是素数。**使用该方法
可以减少遍历的数目，进而提高程序的效率。 
  
看官们，详细的代码如下，大家可以参考： 

 ```
     1	/* **************************
     2	 * For Prime Number
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	#define N 100
     7	
     8	int main()
     9	{
    10		int index,step;
    11		int i = 0;
    12		int res[N]= {0};
    13	
    14		index = step = 0;
    15	
    16		printf("show the PrimeNumber of [1--%d]i\n",N);
    17	
    18		for(index=2; index <=N; ++index)
    19		{
    20			for(step=2; step*step <= N; ++step)
    21			{
    22				if( index != step && index % step == 0 ) //如果不第一个判断条件，那么会有遗漏
    23					break;
    24			}
    25	
    26			if(step*step > N)
    27			{
    28				res[i] = index;
    29				++i;
    30			}
    31		}
    32	
    33		while(i-- >0)
    34			printf("%d \n",res[i]);
    35	
    36		return 0;
    37	}
 ```

各位看官，关于素数的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 
   
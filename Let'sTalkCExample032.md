## 一起talk C栗子吧（第三十二回：C语言实例--再谈最大公约数）

各位看官们，大家好，我们在第九回中一起说过最大公约数的例子，这一回咱们继续说该例子。闲话休提，言归正转。让我们一起talk C栗子吧！ 

关于最大公约数的内容，我们在第九回中提到过，如果大家忘记了的话，可以查看以前的文章。

我们今天继续说最大公约数，说的内容可以看作是对第九回的补充。和第九回一样，我们还是通过辗转相除法来求最大公约数。不过我们在第九回中主要通过循环的方式来实现辗转相除法，今天我们使用另外一种方式来实现辗转相除法。

看官们，详细的代码如下，大家可以参考使用。在代码中我们使用了递归的方法来实现辗转相除法。使用递归实现的代码比较少，看上去很简洁，不过从性能方面来看，该代码的性能比使用循环的代码性能低。

```
     1	/* **************************
     2	 * For Greatest Common Divisor another way
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	int gcd(int a, int b)
     7	{
     8		int temp;
     9	
    10		if(a < b)
    11		{
    12			temp = a;
    13			a = b;
    14			b = temp;
    15		}
    16	
    17		return (b>0)? gcd(b,a%b) :a ;
    18	}
    19	
    20	int main()
    21	{
    22		int v,k;
    23		v = k = 0;
    24	
    25		printf("Please input 2 number for get the GCD of them .\n");
    26		scanf("%d %d",&v,&k);
    27		if(v <0 || k < 0)
    28		{
    29			printf("bad input number \n");
    30			return 0;
    31		}
    32	
    33		printf("the GCD of %d and %d is:%d \n",v,k,gcd(v,k));
    34	
    35		return 0;
    36	}
    37	
```
各位看官，关于最大公约数的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。
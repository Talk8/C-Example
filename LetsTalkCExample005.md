# 一起talk C栗子吧（第五回：C语言实例--数组巧妙赋值）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  
 
看官们，上一回中咱们说的是斐波那契数列的例子，这一回咱们说的例子是：数组巧妙赋值。 
  
看官们，大家如果学习过C语言的话，应该知道给变量赋值的方法为：a=b。它表示把变量b的值赋值给变
量a。当然变量a和b要事先定义好，而且最好是同一种类型。但是a=b这种赋值方法对数组类型的变量就
不起作用了。大家可以看我写的例子。如果把例子中52行的注释去掉的话，就引起编译错误。不过看官们
先不要着急。我在例子中使用了一种方法，可以巧妙地使用a=b这种形式给变量赋值。大家知道，结构体
变量可以使用a=b这种形式去赋值，于是我就在结构体中定义了一个数组类型的变量，当使用结构体变量
以a=b这种形式赋值时，就能把结构体中数组类型的成员也一起赋值，从而**巧妙地使用a=b这种形式给数组
类型的变量赋值。** 
 
看官们，详细的代码如下，请大家参考：

```
     1	/* **************************
     2	 * For ArrayValue-使用a=b这种形式给数组赋值
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	#define LENGTH 5
     7	
     8	typedef struct _array
     9	{
    10		int a[LENGTH];
    11	}Array;
    12	
    13	int main()
    14	{
    15		int i = 0;
    16		int a1[LENGTH] = {0};
    17		int a2[LENGTH] = {0};
    18		Array a3,a4;
    19	
    20		// init array
    21		for(i=0; i<LENGTH; ++i)
    22			a1[i] = i+1;
    23	
    24		//show the value of array
    25		for(i=0; i<LENGTH; ++i)
    26			printf("%d \t",a1[i]);
    27	
    28		printf("\n");
    29	
    30		//init the struct value
    31		for(i=0; i<LENGTH; ++i)
    32			a3.a[i] = i+1;
    33	
    34		//show the struct value
    35		printf("---the value of a3 --- \n");
    36		for(i=0; i<LENGTH; ++i)
    37			printf("%d \t",a3.a[i]);
    38	
    39		printf("\n");
    40	
    41		//init the struct value
    42		for(i=0; i<LENGTH; ++i)
    43			a4.a[i] = i+5;
    44	
    45		//show the struct value
    46		printf("---the value of a4 --- \n");
    47		for(i=0; i<LENGTH; ++i)
    48			printf("%d \t",a4.a[i]);
    49	
    50		printf("\n");
    51	
    52		//a2 = a1;
    53		a4 = a3;
    54		printf("---the value of a4 --- \n");
    55		for(i=0; i<LENGTH; ++i)
    56			printf("%d \t",a4.a[i]);
    57	
    58		printf("\n");
    59	
    60		return 0;
    61	}
```
各位看官，关于数组巧妙赋值的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 
 

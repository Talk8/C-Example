# 一起talk C栗子吧（第十八回：C语言实例--输出十六进制）

各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，言归正转。让我们一起talk C栗子吧！ 

看官们，上一回中咱们说的是栈的例子，这一回咱们说的例子是：输出十六进制。

看官们，我想熟悉C语言的朋友们，对于输出十六进制的内容，肯定都会使用printf函数进行格式化输出。不过，有时候想输出十六进制时就会有点“不识庐山真面目，只缘身在此山中”的感觉。我在前面的例子中
有一个关于进制转换的例子。当时输出十六进制时使用分别判断10到15，然后依据判断结果输出A到F。现在回头看这个例子，就是刚才说的“不识庐山真面目，只缘身在此山中”。为此，我专门把进制转换例子中的
代码进行了修改。使用printf函数中的%X输出十六进制的内容。看官们，详细的代码如下，大家可以参考：
```
     1	/* **************************
     2	 * For Hex output
     3	 * *************************/
     4	#include<stdio.h>
     5	
     6	/*convert function
     7	 *Parameter a is used for saving converting result
     8	 *Parameter iVal is a value ,which will be converted.
     9	 *Parameter base is a base value ,
    10	 */
    11	
    12	#define SUCCESS 0
    13	#define FALSE 1
    14	#define BIT 32
    15	
    16	int convert(int *a,int iVal,int base)
    17	{
    18		int index = 0;
    19		int res = 0;
    20	
    21	
    22		if(NULL == a)// check the pointer
    23		{
    24			printf("null pointer \n");
    25			return FALSE;
    26		}
    27		
    28		if( 0 == base) //check the base, 0 can't be used for division
    29		{
    30			printf("bad value of base \n");
    31			return FALSE;
    32		}
    33	
    34		res = iVal;
    35		//the main algorithm
    36		do
    37		{
    38			*(a+index) = res % base;
    39			res /= base;
    40			++index;
    41		}while(res != 0);
    42	
    43		return SUCCESS;
    44	}
    45	
    46	int showConvertResult(int *a)
    47	{
    48		int index = 0;
    49	
    50		if(NULL == a)// check the pointer
    51		{
    52			printf("null pointer \n");
    53			return FALSE;
    54		}
    55	
    56		for(index=BIT; index>0; --index)
    57		{
    58			if(index %4 == 0)
    59				printf(" ");
    60	
    61			switch( *(a+index-1) ) // input hex character
    62			{
    63			case 10:
    64			case 11:
    65			case 12:
    66			case 13:
    67			case 14:
    68			case 15:
    69				printf("%X",a[index-1]);
    70				break;
    71			default:
    72				printf("%d",a[index-1]);
    73				break;
    74			}
    75		}
    76	
    77		printf("\n");
    78	
    79		return SUCCESS;
    80	}
    81	
    82	int main()
    83	{
    84		int base = 0;
    85		int iVal =0;
    86		int result = 0;
    87		int hex[BIT] = {0}; // the max bit is 32
    88	
    89		printf("please input a number for conversion: \n");
    90		if(0 == scanf("%d",&iVal))
    91		{
    92			printf("Input number is not right \n");
    93			return FALSE;
    94		}
    95	
    96		printf("please select a char for conversion: \n");
    97		printf(" \t ->Decimal conver to  Binary:input 1 : \n");
    98		printf(" \t ->Decimal conver to  Octonary:input 2 : \n");
    99		printf(" \t ->Decimal conver to  Hex:input 3 : \n");
   100	
   101		if(0 == scanf("%d",&base))
   102		{
   103			printf("Input number for selecting is not right \n");
   104			return FALSE;
   105		}
   106	
   107		switch(base)
   108		{
   109		case 1:
   110			result = convert(hex,iVal,2);
   111			break;
   112	
   113		case 2:
   114			result = convert(hex,iVal,8);
   115			break;
   116	
   117		case 3:
   118			result = convert(hex,iVal,16);
   119			break;
   120	
   121		default:
   122			break;
   123	
   124		}
   125	
   126		if(result == FALSE)
   127			return FALSE;
   128		else 
   129		{
   130			showConvertResult(hex);
   131			return SUCCESS;
   132		}
   133	}
```

该例子的代码使用了前面进制转换的代码，只修改了其中输出十六进制的内容，因此该例子也可以看作是进制转换例子的改进版。只所以写该例子就是为了避免“不识庐山真面目，只缘身在此山中”这种感觉。

各位看官，关于输出十六进制的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

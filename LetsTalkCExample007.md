# 一起talk C栗子吧（第七回：C语言实例--进制转换）
 
各位看官们，大家好，从今天开始，我们讲大型章回体科技小说 ：C栗子，也就是C语言实例。闲话休提，
言归正转。让我们一起talk C栗子吧！  
 
看官们，上一回中咱们说的是生成随机数的例子，这一回咱们说的例子是：进制转换。说到进制估计大家
都不陌生，计算机中的进制有二进制，八进制，十进制，十六进制。 

今天咱们将要说的是十进制如何转换成二进制，八进制和十六进制。在这里我把**写程序的步骤和算法思路**
写出来供大家参考。 

- 1.获取用户想要转换的数值和想到转换的进制。这里要检查输入是否正确。这是程序健壮性的体现。
- 2.依据用户输入的不同进制，进行不同的转换。在代码中，我把转换过程封装成了一个函数。
- 3.输出转换后的结果。输出转换后的结果也封装成了一个函数。
    
     
看官们，咱们接下来说说如何进行进制转换，也就是**进制转换函数**的内容。

- 1.使用被转换的数值模转换进制，并且把模的结果保存起来。比如被转换的数值为9,转换进制为2.那么模的
结果 =9%2.该步骤要执行多次，具体的次数由步骤2决定。把每次执行的结果从左到右排列成一排就是转换
进制的结果。在程序中使用一个数组来保存结果。
- 2.使用被转换的数值除以转换进制，并且判断商是否为0.如果不为0重复步骤1和2,直到商等于0为止。
    
     
看官们，说完了转换函数，咱们接下来说说**输出进制转换结果**的函数。 

- 1.输出结果时与转换转换函数中保存结果的顺序正好相反。保存是沿着数组头到尾的方向，输出时是沿着
数组尾到头的方向。两个方向正好相反。
- 2.十六进制的输出结果中包含A-F这些字符，所以专门对它们进行了转换。
 
看官们，详细的代码如下，请大家参考：
```
     1	/* **************************
     2	 * For Hex conversion
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
    64				printf("%c",'A');
    65				break;
    66			case 11:
    67				printf("%c",'B');
    68				break;
    69			case 12:
    70				printf("%c",'C');
    71				break;
    72			case 13:
    73				printf("%c",'D');
    74				break;
    75			case 14:
    76				printf("%c",'E');
    77				break;
    78			case 15:
    79				printf("%c",'F');
    80				break;
    81			default:
    82				printf("%d",a[index-1]);
    83				break;
    84			}
    85		}
    86	
    87		printf("\n");
    88	
    89		return SUCCESS;
    90	}
    91	
    92	int main()
    93	{
    94		int base = 0;
    95		int iVal =0;
    96		int result = 0;
    97		int hex[BIT] = {0}; // the max bit is 32
    98	
    99		printf("please input a number for conversion: \n");
   100		if(0 == scanf("%d",&iVal))
   101		{
   102			printf("Input number is not right \n");
   103			return FALSE;
   104		}
   105	
   106		printf("please select a char for conversion: \n");
   107		printf(" \t ->Decimal conver to  Binary:input 1 : \n");
   108		printf(" \t ->Decimal conver to  Octonary:input 2 : \n");
   109		printf(" \t ->Decimal conver to  Hex:input 3 : \n");
   110	
   111		if(0 == scanf("%d",&base))
   112		{
   113			printf("Input number for selecting is not right \n");
   114			return FALSE;
   115		}
   116	
   117		switch(base)
   118		{
   119		case 1:
   120			result = convert(hex,iVal,2);
   121			break;
   122	
   123		case 2:
   124			result = convert(hex,iVal,8);
   125			break;
   126	
   127		case 3:
   128			result = convert(hex,iVal,16);
   129			break;
   130	
   131		default:
   132			break;
   133	
   134		}
   135	
   136		if(result == FALSE)
   137			return FALSE;
   138		else 
   139		{
   140			showConvertResult(hex);
   141			return SUCCESS;
   142		}
   143	}
```
 
各位看官，关于进制转换的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。 
 

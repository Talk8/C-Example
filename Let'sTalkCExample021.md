##一起talk C栗子吧（第二十一回：C语言实例--表达式求值）

各位看官们，大家好，前几回中咱们说了堆栈的原理，并且举了实际的例子进行解说，这一回咱们说的例
子是：表达式求值。表达式求值和上一回中说的括号匹配一样，都使用了堆栈的原理，大家可以从例子中
看出来，所以我们把它们放在一起。闲话休提，言归正转。让我们一起talk C栗子吧！ 

看官们，我们在这里说的表达式为包含加，减，乘除的四则运算表达式。例如：1+2*3-4/5就是一个四则运
算表达式。这个表达式中，运算符在数字中间，所以我们叫它**中缀表达式**，这也是符合我们思维的一种表
现形式，不过，计算机就不理解中缀表达式了，因为它没有办法像我们一样先进行乘除运算，然后再进行
加减运算，所以我们需要把中缀表达式转换成计算机能理解的**后缀表达式**。“什么是后缀表达式”，这时候
台下有看官在提问了，看官莫急，所谓的后缀表达式就是运算符在数字后面。例如：" 1+2*3-6/3 "这个中缀
表达式可以为" 123*+63/- "这种后缀表达式.

**表达式求值有两个大的步骤：**
- 1.中缀表达式转换为后缀表达式。
- 2.对后缀表达式进行求值。

这两个大的步骤中还有一些小的步骤，接下来我们详细说说这些小步骤。在说之前，我首先说明一个概念：
优先级。优先级代表着先后顺序，举一个日常为生活中的例子：排队买东西的时候，排在队列前面的人，
比排在队列后面人具有优先买东西的权利，我们就可以说：排在队列前面的人买东西的优先级高。优先级
在表达式运算过程中体现为：乘法和除法的优先级比加法和减法的优先级高。也就是我们通常说的先乘除
后加减，这个内容我就不多说了，大家在小学数学中都学过。我们在表达式求值过程中把中缀表达式转换
为后缀表达式也与优先级有关，因为后缀表达式可以去掉运算符的优先级。没有优先级了，计算机就能理
解后缀表达式并对其进行相关的运算。

**中缀表达式转换为后缀表达式的步骤如下：**
- 1.从头到尾依次遍历中缀表达式，每次从表达式中读取一个字符；
- 2.判断步骤1中读取的字符，如果是数字则保存到数组a中，如果是+*等运算符，请看下一个步骤；
- 3.对存放运算符的栈进行出栈操作，把步骤的2中的运算符和刚才出栈的运算符进行优先级比较；
- 4.如果步骤2中的运算符优先级高，那么把参与比较的这两个运算符都入栈。否则看下一步；
- 5.如果步骤2中的运算符优先级低，那么让栈中的运算符继续出栈，并且把出栈的运算符存放数组a中；
- 6.重复步骤4和步骤5,直到出栈运算符的优先级比步骤2中运算符的优先级高为止；
- 7.重复步骤1到步骤6.直到遍历完中缀表达式为止；
- 8.判断栈中是否还有运算符，如果有的话，就把所有运算符出栈，并且把出栈的运算符存放数组a中。

**对后缀表达式求值的步骤如下：**
- 1.从头到尾依次遍历后缀表达式，每次从表达式中读取一个字符；
- 2.判断步骤1中读取的字符，如果是数字则入栈，如果是+*等运算符，请看下一个步骤；
- 3.对存放数字的栈进行两次出栈操作，依据步骤2中运算符的类型，对出栈的两个数字进行运算；
- 4.对步骤3中的运算结果进行入栈操作，这样可以把运算结果保存到存放数字的栈中；
- 5.重复步骤1到步骤4.直到遍历完后缀表达式为止；
- 6.栈中最后一个元素就是该表达式的运算结果。

看官们，详细的代码如下，请大家参考：
```
     1	/* **************************
     2	 * Head file of Expression Evaluation
     3	 * *************************/
     4	#ifndef EXPRESSION_EVALUATION_H
     5	#define EXPRESSION_EVALUATION_H
     6	
     7	#include<stdio.h>
     8	#include<stdlib.h>
     9	
    10	#define SUCCESS 0
    11	#define FAILE 1
    12	
    13	#define LEN 20 //栈的长度先定义为5,需要时可自行修改
    14	
    15	typedef char StackElmt; //把char当作栈中元素的类型，实际中可以使用其它的类型或者自己定义一个元素类型
    16	typedef struct _Stack{
    17		StackElmt *base;
    18		StackElmt *top;
    19		int size;
    20	}Stack;
    21	
    22	StackElmt STACK[LEN+1] = {0}; //顺序存储方式的栈,防止数组越界，最后一个位置不放元素
    23	
    24	//声明函数原型，这里有入栈和出栈操的函数
    25	int StackInit(Stack *s);
    26	int StackDestroy(Stack *s);
    27	int StackPrint(Stack *s);
    28	int StackPush(Stack *s, StackElmt e);
    29	int StackPop(Stack *s, StackElmt *e);
    30	
    31	#endif /* EXPRESSION_EVALUATION_H */

```
```
     1	/* **************************
     2	 * Soure file of Expression Evaluation
     3	 * *************************/
     4	
     5	#include"ExpressionEvaluation.h"
     6	
     7	//实现栈相关的函数，为了方便,放到了主函数所在的文件中，最好是单独建立实现函数的源文件
     8	//初始化中栈
     9	int StackInit(Stack *s)
    10	{
    11		if(NULL == s)
    12			return FAILE;
    13	
    14		s->top = s->base = &STACK[0];
    15		s->size = 0;
    16	
    17	}
    18	int StackDestroy(Stack *s)
    19	{
    20		int i =0;
    21	
    22		if(NULL == s)
    23			return FAILE;
    24	
    25		while(i<LEN)
    26		{
    27			STACK[i] = 0;
    28			i++;
    29		}
    30		s->top = s->base = NULL;
    31		s->size = 0;
    32	}
    33	//输出栈中存放的元素
    34	int StackPrint(Stack *s)
    35	{
    36		int index = 0;
    37	
    38		if(NULL == s)
    39			return FAILE;
    40	
    41		if(s->size == 0)
    42		{
    43			printf("the Stack is empty,there is not any element \n");
    44			return FAILE;
    45		}
    46	
    47		while(index < (s->size))
    48		{
    49			printf("%d  ",*((s->base)+index) );
    50			index++;
    51		}
    52	
    53		printf("\n ");
    54	
    55		return SUCCESS;
    56	}
    57	
    58	//入栈函数,top指向栈顶,先把元素入栈,然后向栈顶移动一位
    59	int StackPush(Stack *s, StackElmt e)
    60	{
    61		if(NULL == s)
    62			return FAILE;
    63	
    64		if(s->size >= LEN)
    65		{
    66			printf("the Stack is full \n");
    67			return FAILE;
    68		}
    69	
    70		*(s->top) = e;
    71		(s->top)++;
    72		(s->size)++;
    73	
    74		return SUCCESS;
    75	}
    76	
    77	//出栈函数,top先向栈底移到一位，然后移出当前它所指向的元素
    78	int StackPop(Stack *s, StackElmt *e)
    79	{
    80		if(NULL == s)
    81			return FAILE;
    82	
    83		if(s->size == 0)
    84		{
    85			//printf("the Stack is empty \n");
    86			return FAILE;
    87		}
    88	
    89		(s->top)--;
    90		*e = *(s->top);
    91		(s->size)--;
    92	
    93		return SUCCESS;
    94	}
    95	
    96	int main()
    97	{
    98		char ch = '\0';
    99		char str[2];
   100		char *a1= "1+2*3-6/3"; // 存放中缀表达式
   101		//char *a1="1+2+3*4";
   102		char a2[LEN]={'\0'}; // 存放后缀表达式
   103		Stack s;
   104		int i,j;
   105		int a,b;
   106		int res = 0;
   107		int stack[LEN] ={0};
   108	
   109		i = j = a = b = 0;
   110		StackInit(&s);
   111	
   112		while(*(a1+i) != '\0') //遍历中缀表达式
   113		{
   114			printf("%c",*(a1+i));
   115	
   116			if(*(a1+i) == '+' || *(a1+i) == '-')
   117			{
   118				if(s.size != 0)
   119				{
   120					while( s.size >= 0 && !StackPop(&s,&ch))
   121					{
   122						*(a2+j) = ch;
   123						ch = '\0';
   124						j++;
   125					}
   126					StackPush( &s,*(a1+i) );
   127				}
   128				else
   129					StackPush(&s,*(a1+i));
   130			}
   131			else if( *(a1+i) == '*' || *(a1+i) == '/')
   132			{
   133				if(s.size != 0)
   134				{
   135					if(!StackPop(&s,&ch))
   136					{
   137						if(ch == '+' || ch == '-')
   138						{
   139							StackPush(&s,ch);
   140							StackPush( &s,*(a1+i) );
   141						}
   142						else
   143						{
   144							StackPush(&s,ch);
   145							while( !StackPop(&s,&ch) && (ch == '*' || ch == '/') )
   146							{
   147								*(a2+j) = ch;
   148								ch = '\0';
   149								j++;
   150							}
   151							StackPush( &s,*(a1+i) );
   152						}
   153					}
   154				}
   155				else
   156					StackPush(&s,*(a1+i));
   157			}
   158			else //从中缀表达式中读取的字符是数字，保存到数组中
   159			{
   160				*(a2+j) = *(a1+i);
   161				j++;
   162			}
   163	
   164			i++;
   165		}
   166	
   167		while( s.size >= 0 && !StackPop(&s,&ch)) //栈中还有运算符的话，需要全部取出，放到后缀表达式中
   168		{
   169			*(a2+j) = ch;
   170			ch = '\0';
   171			j++;
   172		}
   173		*(a2+j) = '\0';
   174	
   175		i=j=0;
   176		StackDestroy(&s);
   177		StackInit(&s);
   178	
   179		while(*(a2+i) != '\0') //遍历后缀表达式
   180		{
   181			if(*(a2+i) == '+')
   182			{
   183				j--;
   184				a = stack[j];
   185				j--;
   186				b = stack[j];
   187	
   188				stack[j]= a+b;
   189				j++;
   190			}
   191			else if(*(a2+i) == '-')
   192			{
   193				j--;
   194				a = stack[j];
   195				j--;
   196				b = stack[j];
   197	
   198				stack[j]= b-a;
   199				j++;
   200			}
   201			else if(*(a2+i) == '*')
   202			{
   203				j--;
   204				a = stack[j];
   205				j--;
   206				b = stack[j];
   207	
   208				stack[j]= a*b;
   209				j++;
   210			}
   211			else if(*(a2+i) == '/')
   212			{
   213				j--;
   214				a = stack[j];
   215				j--;
   216				b = stack[j];
   217	
   218				stack[j]= b/a;
   219				j++;
   220			}
   221			else
   222			{
   223				str[0] =*(a2+i);
   224				str[1] ='\0';
   225				stack[j]= atoi(str);
   226				j++;
   227			}
   228	
   229			i++;
   230		}
   231		res =stack[0];
   232	
   233		printf(" = %d ",res);
   234		printf("\n");
   235		return SUCCESS;
   236	}
```
从代码中可以看到，我们用了两次栈，一次是在中缀表达式转换成后缀表达式的过程中，栈用来存放运算
符。另外一次是在后缀表达式求值的过程中，栈用来存放参与运算的数字。

各位看官，关于表达式求值的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

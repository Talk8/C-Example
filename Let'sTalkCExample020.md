## 一起talk C栗子吧（第二十回：C语言实例--括号匹配）

各位看官们，大家好，前几回中咱们说了堆栈的原理，并且举了实际的例子进行解说，这一回咱们说的例
子是：括号匹配。括号匹配使用了堆栈的原理，大家可以从例子看出来，所以我们把它们放在一起。闲话
休提，言归正转。让我们一起talk C栗子吧！ 

看官们，所谓的括号匹配，就是给了一连串括号，里面有各种类型的的括号，然后确定该串中的括号是否
是一一 匹配的。例如：({[]})这串括号中的括号就是匹配的。因为串中的括号都是成对出现。(({)这串括号就
不是匹配的，串中{没有与它配对的括号，而且与(匹配的括号数量也不正确。

在确认括号是否匹配的过程中，我们的思路是这样的：首先依次从串中读取括号，每次读取一个括号，如
果读取的括号是左括号，比如(,{,[，那么就让括号入栈，如果读取的是右括号，比如),},]，那么就把栈顶的
括号取出来，和它匹配，如果匹配，就继续进行判断串中的下一个括号，如果不匹配，那么就说明该串中
的括号不匹配。

看官们，详细的代码如下，请大家参考：

```
     1	/* **************************
     2	 * For ParenthesisMatching
     3	 * *************************/
     4	
     5	#include<stdio.h>
     6	
     7	#define SIZE 10
     8	
     9	char array[SIZE]; //using the array for stack
    10	typedef struct _Stack
    11	{
    12		char *top;
    13		int size;
    14	}Stack;
    15	
    16	int push(Stack *s,char ch)
    17	{
    18		if(NULL == s)
    19			return 0;
    20	
    21		if(s->size < SIZE)
    22		{
    23			*(s->top) = ch;
    24			s->top++;
    25			s->size++;
    26	
    27			return 1;
    28		}
    29		else
    30			return 0;
    31	}
    32	
    33	int pop(Stack *s, char *ch)
    34	{
    35		if(NULL == s)
    36			return 0;
    37	
    38		if(s->size > 0)
    39		{
    40			s->top--;
    41			s->size--;
    42			*ch = *(s->top);
    43	
    44			return 1;
    45		}
    46		else
    47			return 0;
    48	}
    49	
    50	int main()
    51	{
    52		char parenthesis[SIZE]={'(','{','[',']','}',')','[','{','}',']'}; // parenthesis ,you can init it by your self
    53		int i;
    54		int result;
    55		char ch;
    56		Stack s ; // stack defination and init
    57		s.top = &array[0];
    58		s.size =0;
    59	
    60		result =0;
    61		for(i=0; i<SIZE; ++i)
    62		{
    63			ch = parenthesis[i];
    64	
    65			switch(ch)
    66			{
    67				case '(':
    68				case '{':
    69				case '[':
    70					if(!push(&s,ch) )
    71						return 0;
    72					break;
    73				case ')':
    74					if(!pop(&s,&ch))
    75						return 0;
    76	
    77					if( ch != '(')
    78					{
    79						result = 1;
    80					}
    81					break;
    82				case '}':
    83					if(!pop(&s,&ch))
    84						return 0;
    85	
    86					if( ch != '{')
    87					{
    88						result = 1;
    89					}
    90					break;
    91				case ']':
    92					if(!pop(&s,&ch))
    93						return 0;
    94	
    95					if( ch != '[')
    96					{
    97						result = 1;
    98					}
    99					break;
   100				default:
   101					break;
   102			}
   103	
   104			if(1 == result)
   105			{
   106				printf("Parenthesis is not matching \n");
   107				break;
   108			}
   109		}
   110	
   111		if(0 == result)
   112		{
   113			printf("Parenthesis is matching \n");
   114		}
   115	
   116		return 0;
   117	}

```

各位看官，关于括号匹配的例子咱们就说到这里。欲知后面还有什么例子，且听下回分解。

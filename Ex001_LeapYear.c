/* **************************
 * For Leap Year
 * *************************/
#include<stdio.h>

#define SUCCESS 1
#define FAILED  0
#define BAD_PARAMETERS -1

int LeapYear(int year)
{
	int result = 0;
	if(year <=0 || year >9999)
	{
		printf("The year is not a correct year,(between 0 - 9999 )\n");
		return BAD_PARAMETERS;
	}

	if( (year % 400 == 0)
	||  ((year % 4 == 0) && (year % 100 != 0)) )
		return SUCCESS;
	else
		return FAILED;

}
int main()
{
	int year, result;
	year = result = 0;

	printf("Please input a year,such as 2015 \n");
	scanf("%d",&year);
	result = LeapYear(year);

	if(result == SUCCESS)
		printf("It is a Leap Year \n");
	else if(result == FAILED)
		printf("It is not a Leap Year \n");
	else
		printf("Please check you input years \n");

	return 0;
}

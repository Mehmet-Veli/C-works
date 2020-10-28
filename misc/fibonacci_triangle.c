/**
 * @file fibonacci_triangle.c
 * @brief using fibonacci series we can print triangle of numbers
 */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
/**
 * @brief Function to print Fibonacci series in triangle format
 * @param [in] n index of Fibonacci number to get
 */
int fibo(int n)

{
	int i,j,a,b,c;
	for(i=1;i<=n;i++)
	{
		a=0; //initialize first number
		b=1; //initialize second number
		printf("%d\t",b);
		for(j=1;j<i;j++) //printing series in loop till n
		{
			c=a+b;
			printf("%d\t",c); 
			a=b;
			b=c;
		}
		printf("\n"); //next line after every series till n
	}
	return -1;
}
/**
 * Test implementations
 * @returns void
 */
static void test()
{
	assert(fibo(5)); //giving value of n to test
}
/**
 * Driver Code
 * @returns 0 on exit
 */
int main()
{
	test(); // execute the tests
	return 0;
}

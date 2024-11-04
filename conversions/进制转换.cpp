#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

const char f[]="0123456789ABCDEF";
void A(int n,int m)
{
	int i=0;
	char a[1000];
	while(n)
	{
		a[i]=f[n%m];
		n=n/m;
		i++;
	}
	while(i--)
	    printf("%c",a[i]);
}

void B(int n,int m)
{
	if(n<m)
	{
		if(n<10)
		    printf("%d",n);
		else
		    printf("%c",n-10+'A');
	}
	else
	{
		B(n/m,m);
		if(n%m<10)
		    printf("%d",n%m);
		else
		    printf("%d",n%m-10+'A');
	}
}

int main()
{
	int i,j;
	printf("输入数字：\n");
	scanf("%d",&i);
	printf("输入要转换的进制：\n");
	scanf("%d",&j);
	printf("输出转换后的数字：");
	B(i,j);
	printf("\n");
	A(i,j);
	system("pause");
	return 0;
}

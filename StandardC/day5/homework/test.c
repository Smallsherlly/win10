#include<stdio.h>
#include<assert.h>
#include<string.h>
int iNum(char (*s1)[20],const char *s2)
{
	char *ps[4] ={s1[0],s1[1],s1[2],s1[3]};
	size_t n = 0;
	assert(*s1!=NULL&&s2!=NULL);
	while(*s2!='\0')
	{
		while(*s2!=' '&&*s2!='\0')
		{
			strncat(*(ps+n),s2++,1);
		}
		n++;
		s2++;
	}
	return n;
}

int main()
{
	char arr[20] = {0};
	char brr[4][20] = {0};
	//char *crr[4] = {brr[0],brr[1],brr[2],brr[3]};
	int n = 0;
	gets(arr);
	
	//printf("%s",arr);
	n = iNum(brr,arr);
	printf("%d\n",n);
	
	for(int i = 0;i < n;i++)
		printf("%s ",*(brr+i));
	printf("\n");
	return 0;	
}

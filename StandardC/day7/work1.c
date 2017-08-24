#include<stdio.h>
#include<string.h>
void *mymemcpy(void *dest,const void *src,size_t n)
{
	char *pdest = (char*)dest;
	char *psrc  = (char*)src;
	if(NULL == dest||NULL == src)
	{
		return NULL;
	}
	if(pdest < psrc+n&&psrc < pdest)
	{	
		for(int i = n-1;i >= 0;i--)
		{
			*(pdest+i)= *(psrc+i);
		}
	}else{
		for(int i = 0;i < n;i++)
		{
			*(pdest+i)= *(psrc+i);
		}
	}
	
	
	return dest;
		
}
int main()
{
	//int  a  = 0x12345678;
	char grr = 's';
	char arr[20] = "abcdefgh" ;
	char brr[20] = "abcdefgh" ;
	mymemcpy(arr+1,arr,6);
	memcpy(brr+1,brr,6);
	memcpy(&grr,arr,1);	
	printf("%s\n",arr);
	printf("%c\n",grr);

	
	return 0;	
}



#include "stdlib.h"
#include "stdio.h"


void main( int argc, char *argv[] )
{
	FILE *fp ;
	char *strBuffer ;
	int	 nFileLen ;
	char *strFileName;
	strFileName="c:/yefeng.txt";

	if((fp = fopen(strFileName , "r")) == NULL)
	{
		printf("没有文件");
		return ;
	}

	fseek(fp, 0 , SEEK_END  ) ;
	nFileLen = ftell(fp) ;
	printf("yefeng.txt文件件的长度是%d bytes\n", nFileLen);
	
	strBuffer = (char *)malloc(nFileLen * sizeof(char)) ;

	if(strBuffer == NULL)
	{
		printf("不能分配空间");
		return ;
	}

	fseek(fp , SEEK_SET , 0 );
	fread(strBuffer , 1 ,nFileLen, fp) ;
	
	fclose(fp) ;

	printf(strBuffer);
}

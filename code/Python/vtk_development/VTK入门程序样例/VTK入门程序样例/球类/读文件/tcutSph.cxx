

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
		printf("û���ļ�");
		return ;
	}

	fseek(fp, 0 , SEEK_END  ) ;
	nFileLen = ftell(fp) ;
	printf("yefeng.txt�ļ����ĳ�����%d bytes\n", nFileLen);
	
	strBuffer = (char *)malloc(nFileLen * sizeof(char)) ;

	if(strBuffer == NULL)
	{
		printf("���ܷ���ռ�");
		return ;
	}

	fseek(fp , SEEK_SET , 0 );
	fread(strBuffer , 1 ,nFileLen, fp) ;
	
	fclose(fp) ;

	printf(strBuffer);
}

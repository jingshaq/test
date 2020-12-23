# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "17打印所有重定位信息.h"

DWORD main17()
{
	DWORD ret = 0;
	DWORD length = 0;
	void *Filepath = "C:/MyDll.dll";
	void *FileAdd = NULL;

	ret = FileLength17(Filepath, &length);
	if (ret != 0)
	{
		printf("func FileLength17 error \n");
		return ret;
	}
	ret = FileRead17(Filepath, length, &FileAdd);
	if (ret != 0)
	{
		printf("func FileRead17 error \n");
		return ret;
	}
	ret = PrintReLoctionInformation(FileAdd);
	if (ret != 0)
	{
		printf("func PrintReLoctionInformation error \n");
		return ret;
	}

	free(FileAdd);
	system("pause");
	return ret;
}
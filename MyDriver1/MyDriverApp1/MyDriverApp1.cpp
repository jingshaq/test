// MyDriverApp1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	HANDLE hdevice = NULL;
	hdevice = CreateFile(L"\\\\.\\MyFirstDevice", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
	{
		printf("Open Device Fail.\n");
		system("pause");
		return 0;
	}

	printf("Open Device Success.\n");

	CloseHandle(hdevice);
	system("pause");
    return 0;
}


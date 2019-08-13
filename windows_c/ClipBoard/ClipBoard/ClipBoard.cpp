// ClipBoard.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main(int argc, char * argv[])
{
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	char * content = "剪切板新数据";   // 待写入数据
	int contentSize = strlen(content) + 1;

	if (!OpenClipboard(NULL))    // 打开剪切板，打开后，其他进程无法访问
	{
		puts("剪切板打开失败");
		return 1;
	}

	//HANDLE hMem = GetClipboardData(CF_TEXT); // 文本
	//if (hMem)
	//{
	//	LPSTR lpStr = (LPSTR)GlobalLock(hMem);
	//	if (lpStr != NULL)
	//	{
	//		puts(lpStr);
	//		GlobalUnlock(hMem);
	//	}
	//}
	//else
	//{
	//	puts("获取剪切板数据失败");
	//	return 1;
	//}

	HGLOBAL hGlobal = GetClipboardData(CF_HDROP); // 文件
	if (hGlobal)
	{
		HDROP hDrop = (HDROP)GlobalLock(hGlobal);
		if (hDrop)
		{
			UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, 0, 0);
			UINT filenameLength;
			for (UINT i = 0; i < fileCount; ++i)
			{
				filenameLength = DragQueryFile(hDrop, i, 0, 0);
				TCHAR lpszFileName[256];
				DragQueryFile(hDrop, i, lpszFileName, filenameLength + 1);
				_tprintf(_T("%s\n"), lpszFileName);
			}
		}
	}
	else
	{
		puts("获取剪切板数据失败");
		return 1;
	}


	if (!EmptyClipboard())       // 清空剪切板，写入之前，必须先清空剪切板
	{
		puts("清空剪切板失败");
		CloseClipboard();
		return 1;
	}

	if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) == NULL)    // 对剪切板分配内存
	{
		puts("内存赋值错误!!!");
		CloseClipboard();
		return 1;
	}

	if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)             // 将内存区域锁定
	{
		puts("锁定内存错误!!!");
		CloseClipboard();
		return 1;
	}

	memcpy_s(lpMemory, contentSize, content, contentSize);   // 将数据复制进入内存区域

	GlobalUnlock(hMemory);                   // 解除内存锁定

	if (SetClipboardData(CF_TEXT, hMemory) == NULL)
	{
		puts("设置剪切板数据失败!!!");
		CloseClipboard();
		return 1;
	}

	system("pause");
	return 0;
}


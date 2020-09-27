// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <Winsock2.h>
#include <Winbase.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define FLATJMPCODE_LENGTH 5            //x86 平坦内存模式下，绝对跳转指令长度
#define FLATJMPCMD_LENGTH  1            //机械码0xe9长度
#define FLATJMPCMD         0xe9         //对应汇编的jmp指令

// 记录被打桩函数的内容，以便恢复
BYTE g_apiBackup[FLATJMPCODE_LENGTH + FLATJMPCMD_LENGTH];

bool setStub(LPVOID ApiFun, LPVOID HookFun)
{
	HANDLE file_handler = GetCurrentProcess();           //获取进程伪句柄
	DWORD oldProtect, TempProtectVar;
	char newCode[6];                                     //用于读取函数原有内存信息
	int SIZE = FLATJMPCODE_LENGTH + FLATJMPCMD_LENGTH;     //需要修改的内存大小
	if (!VirtualProtectEx(file_handler, ApiFun, SIZE, PAGE_READWRITE, &oldProtect))  //修改内存为可读写
	{
		OutputDebugStringA("VirtualProtectEx faild 1 \n");
		return false;
	}
	if (!ReadProcessMemory(file_handler, ApiFun, newCode, SIZE, NULL))              //读取内存
	{
		OutputDebugStringA("ReadProcessMemory faild \n");
		return false;
	}

	OutputDebugStringA("process setStub\n");
	memcpy((void*)g_apiBackup, (const void*)newCode, sizeof(g_apiBackup));      //保存被打桩函数信息
	*(BYTE*)ApiFun = FLATJMPCMD;
	*(DWORD*)((BYTE*)ApiFun + FLATJMPCMD_LENGTH) = (DWORD)HookFun - (DWORD)ApiFun - FLATJMPCODE_LENGTH;   //桩函数注入 
	BOOL b = VirtualProtectEx(file_handler, ApiFun, SIZE, oldProtect, &TempProtectVar);  //恢复保护属性
	if (b) {
		OutputDebugStringA("success over!\n");
	}
}


int WINAPI test(SOCKET s, char *buf, int len, int flags)
{
	OutputDebugStringA("test hook\n");
	int tmpRet = 0; 
	memcpy(buf, "hello\n", 6);
	tmpRet = 6;
	return tmpRet;
}


BOOL APIENTRY DllMain(HMODULE /* hModule */, DWORD ul_reason_for_call, LPVOID /* lpReserved */)
{
	char *path = "C:\\test\\attach.txt";
	DWORD dwWrite = 0;
	HANDLE hFile = NULL;
	HMODULE h = NULL;
	BYTE* v = NULL;
	OutputDebugStringA("Hook DllMain\n");
	char buf[1024] = { 0 };

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		typedef int(*proc)();
		h = LoadLibraryA("Ws2_32.dll");
		v = (BYTE*)GetProcAddress(h, "recv");
		setStub(v, test);
		sprintf_s(buf, 1024, "pid=%d", GetCurrentProcessId());
		OutputDebugStringA(buf);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}





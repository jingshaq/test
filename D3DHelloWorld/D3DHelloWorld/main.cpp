//-----------------------------------------------------------------------------
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // 禁用过时警告
#include <strsafe.h>
#pragma warning( default : 4996 )




//-----------------------------------------------------------------------------
// 全局变量
//-----------------------------------------------------------------------------
LPDIRECT3D9         g_pD3D = NULL; // 用于创建D3D设备
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // 我们的渲染设备




										 //-----------------------------------------------------------------------------
										 // Name: InitD3D()
										 // Desc: 初始化 Direct3D
										 //-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// 创建D3D的对象，这是需要创建D3DDevice。
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.
	/*ZeroMemory()　ZeroMemory宏用0来填充一块内存区域。
	　　为了避免优化编译器的意外的影响，请使用SecureZeroMemory函数。
	  　　void ZeroMemory(
		　　PVOID Destination,
		  　　SIZE_T Length
			　　);
			  　　参数：
				　　Destination :指向一块准备用0来填充的内存区域的开始地址。
				  　　Length :准备用0来填充的内存区域的大小，按字节来计算。
					　　返回值：无
					  　　ZeroMemory 只是将指定的内存块清零.
						　　使用结构前清零, 而不让结构的成员数值具有不确定性, 是一个好的编程习惯
						  */

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;    //不是全屏
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//创建Direct3D 设备. 在这里，我们使用默认的适配器 (大多数的
	// 系统只有一块显卡, 除非我们有多卡互联）
	//  和需要硬件抽象层 (就像我们希望的是硬件设备而非软件
	// 当我们想知道它在所有的卡上都可以使用的时，我们
	//会使用软件顶点处理 。对于支持硬件顶点处理的显卡，会有性能上的较大提升

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// 设备状态通常会设定在这里

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: 释放预先初始化的对象
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: 绘制场景
//-----------------------------------------------------------------------------
VOID Render()
{
	if (NULL == g_pd3dDevice)
		return;

	// 清除后台缓冲区为蓝色
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// 场景开始
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Rendering of scene objects can happen here

		// 场景结束
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: 窗体消息句柄
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: 应用程序的入口
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// 注册窗体类
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx(&wc);

	// 创建应用程序窗口
	HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 01: CreateDevice",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		NULL, NULL, wc.hInstance, NULL);

	// 初始化 Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// 显示窗体
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// 进入消息循环
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	return 0;
}
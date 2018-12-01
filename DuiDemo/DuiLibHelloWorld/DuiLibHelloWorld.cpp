// HelloWorld.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"
#include "DuiLibHelloWorld.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd窗口"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.ShowModal();
	return 0;
}

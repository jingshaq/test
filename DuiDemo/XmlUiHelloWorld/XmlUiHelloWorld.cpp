#include "stdafx.h"
#include "XmlUiHelloWorld.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());// 设置资源的默认路径（此处设置为和exe 在同一目录）
	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd窗口"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}

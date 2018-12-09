#pragma once
#include "stdafx.h"
#include "DuiMenu.h"

class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName() const {
		return _T("DUIMainFrame");
	}
	virtual CDuiString GetSkinFile() {
		return _T("DuiLibPaintControlDemo.xml");
	}
	virtual CDuiString GetSkinFolder() { return _T(""); }

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("btnMenu"))
			{
				POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
				CDuiMenu *pMenu = new CDuiMenu(_T("Menu/menu.xml"));
				pMenu->Init(*this, pt);
				pMenu->ShowWindow(TRUE);
			}
		}
		__super::Notify(msg);
	}
};

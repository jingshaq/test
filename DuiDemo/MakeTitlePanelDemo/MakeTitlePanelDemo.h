#pragma once
#include "stdafx.h"

class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName() const {
		return _T("DUIMainFrame");
	}
	virtual CDuiString GetSkinFile() {
		return _T("MakeTitlePanelDemo.xml");
	}
	virtual CDuiString GetSkinFolder() { return _T(""); }
};
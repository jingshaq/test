#pragma once
#include "stdafx.h"

class CPage1 : public CNotifyPump
{
public:
	CPage1();
	virtual LPCTSTR GetWindowClassName() const { return _T("CPage1"); }
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);
private:
	CPaintManagerUI* m_pPaintManager;
};

class CDuiFrameWnd : public WindowImplBase
{
public:
	CDuiFrameWnd() {
		m_Page1.SetPaintMagager(&m_PaintManager);
		AddVirtualWnd(_T("page1"), &m_Page1);
	}
	~CDuiFrameWnd() {
		RemoveVirtualWnd(_T("page1"));
	}
	virtual LPCTSTR GetWindowClassName() const { return _T("CDuiFrameWnd"); }

	virtual CDuiString GetSkinFile() {
		return _T("CNotifyPumpDemo.xml");
	}
	virtual CDuiString GetSkinFolder() { return _T(""); }
	void CDuiFrameWnd::OnFinalMessage(HWND hWnd) {
		__super::OnFinalMessage(hWnd);
		delete this; 
	}
	void CDuiFrameWnd::Notify(TNotifyUI &msg)
	{
		return WindowImplBase::Notify(msg);
	}


	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);

protected:
	CPaintManagerUI m_PaintManager;
	CPage1 m_Page1;
};

#pragma once
#include "stdafx.h"

class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame测试类"); }
	virtual void Notify(TNotifyUI& msg) 
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("btnHello"))
			{
				::MessageBox(NULL, _T("我是按钮"), _T("点击了按钮"), NULL);
			}
		}
	}
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		if (uMsg == WM_CREATE)
		{
			CControlUI *pWnd = new CButtonUI;
			pWnd->SetName(_T("btnHello")); // 设置控件的名称，这个名称用于标识每一个控件，必须唯一，相当于MFC 里面的控件ID
			pWnd->SetText(_T("Hello World 窗口")); // 设置文字
			pWnd->SetBkColor(0xFF00FF00); // 设置背景色
			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this); // 添加控件等消息响应，这样消息就会传达到duilib 的消息循环，我们可以在Notify 函数里做消息处理
			return lRes;
		}
		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}
		return __super::HandleMessage(uMsg, wParam, lParam);
	}
protected:
	CPaintManagerUI m_PaintManager;
};

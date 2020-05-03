#pragma once
#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "CCustomButton.h"
#include "CScreen.h"
#include "CGreenHell.h"
#include "CPatcher.h"


class CMainWindow : public CFrameWnd
{
	DECLARE_DYNAMIC(CMainWindow)

public:
	CMainWindow();
	virtual ~CMainWindow();

protected:
	DECLARE_MESSAGE_MAP()
	
	HBRUSH m_Background;
	CCustomButton* m_CmdExit;
	CCustomButton* m_CmdPatch;
	CScreen* m_Screen;
	CGreenHell m_Greenhell;
	CPatcher m_Patcher;
	BOOL m_IsPatched;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPatch();
	afx_msg void OnExit();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


#endif

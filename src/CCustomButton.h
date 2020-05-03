#pragma once
#ifndef CCUSTOMBUTTON_H
#define CCUSTOMBUTTON_H

#include "framework.h"
#include <gdiplus.h>


class CCustomButton : public CButton
{
	DECLARE_DYNAMIC(CCustomButton)

public:
	CCustomButton(CWnd *parent, DWORD id, DWORD x, DWORD y, UINT resUp, UINT resDown, UINT resHover);
	virtual ~CCustomButton();

protected:
	DECLARE_MESSAGE_MAP()

	const Gdiplus::Bitmap* m_State;
	Gdiplus::Bitmap* m_Up;
	Gdiplus::Bitmap* m_Down;
	Gdiplus::Bitmap* m_Hover;
	Gdiplus::Rect m_Viewport;

	void SetState(const Gdiplus::Bitmap* const state);

private:
	BOOL m_IsDown;
	BOOL m_IsOver;
	
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


#endif

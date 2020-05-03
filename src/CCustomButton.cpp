#include "CCustomButton.h"
#include "global.h"

using namespace Gdiplus;


IMPLEMENT_DYNAMIC(CCustomButton, CButton)

CCustomButton::CCustomButton(CWnd *parent, DWORD id, DWORD x, DWORD y, UINT resUp, UINT resDown, UINT resHover) :
	m_Hover(nullptr),
	m_State(nullptr),
	m_IsDown(FALSE),
	m_IsOver(FALSE)
{
	HINSTANCE instance = AfxGetInstanceHandle();
	this->m_Up = Bitmap::FromResource(instance, MAKEINTRESOURCEW(resUp));
	this->m_Down = Bitmap::FromResource(instance, MAKEINTRESOURCEW(resDown));
	if (resHover)
		this->m_Hover = Bitmap::FromResource(instance, MAKEINTRESOURCEW(resHover));

	this->m_State = this->m_Up;

	this->Create(
		nullptr, 
		WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 
		{ (LONG)x, (LONG)y, (LONG)(x + this->m_Up->GetWidth()), (LONG)(y + this->m_Up->GetHeight()) },
		parent,
		id
	);
	
	this->ShowWindow(SW_SHOW);
	this->UpdateWindow();
}

CCustomButton::~CCustomButton()
{
	this->m_State = nullptr;
	SAFE_DELETE(this->m_Up);
	SAFE_DELETE(this->m_Down);
	SAFE_DELETE(this->m_Hover);
}

void CCustomButton::SetState(const Gdiplus::Bitmap* const state)
{
	if (this->m_State == state)
		return;

	this->m_State = state;
	this->Invalidate(FALSE);
}

BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CCustomButton::DrawItem(LPDRAWITEMSTRUCT ps)
{
	Graphics gx(ps->hDC);
	gx.DrawImage((Gdiplus::Image*)this->m_State, 0, 0);
}


void CCustomButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!this->m_IsOver)
	{
		this->m_IsOver = TRUE;

		if (this->m_IsDown)
			this->SetState(this->m_Down);
		else
			this->SetState(this->m_Hover);
	}

	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = this->m_hWnd;
	tme.dwHoverTime = HOVER_DEFAULT;
	TrackMouseEvent(&tme);

	CButton::OnMouseMove(nFlags, point);
}


void CCustomButton::OnMouseLeave()
{
	if (this->m_IsOver)
	{
		this->m_IsOver = FALSE;
		this->SetState(this->m_Up);
	}

	CButton::OnMouseLeave();
}


void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!this->m_IsDown)
	{
		this->m_IsDown = TRUE;
		this->SetState(this->m_Down);
	}
	
	CButton::OnLButtonDown(nFlags, point);
}


void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this->m_IsDown)
	{
		this->m_IsDown = FALSE;
		this->SetState(this->m_Hover);
	}
	
	CButton::OnLButtonUp(nFlags, point);
}


void CCustomButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	const MSG* msg = this->GetCurrentMessage();
	DefWindowProc(WM_LBUTTONDOWN, msg->wParam, msg->lParam);
}

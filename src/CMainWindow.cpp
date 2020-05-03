#include "Global.h"
#include "Resource.h"
#include "CMainWindow.h"
#include "CCustomButton.h"
#include "CScreen.h"


IMPLEMENT_DYNAMIC(CMainWindow, CFrameWnd)

CMainWindow::CMainWindow() :
	m_Background(nullptr),
	m_CmdExit(nullptr),
	m_CmdPatch(nullptr),
	m_Screen(nullptr),
	m_Greenhell(),
	m_Patcher(),
	m_IsPatched(FALSE)
{
	this->m_Screen = new CScreen();
	this->Create(nullptr, nullptr);

	this->m_CmdPatch = new CCustomButton(this, ID_PATCH, 87, 570, IDB_PATCHUP, IDB_PATCHDOWN, IDB_PATCHHOVER);
	this->m_CmdExit = new CCustomButton(this, ID_EXIT, 87, 625, IDB_EXITUP, IDB_EXITDOWN, IDB_EXITHOVER);

	this->SetTimer((UINT_PTR)ID_RENDERTIMER, 1000 / 60, nullptr);

	this->ShowWindow(SW_SHOW);
	this->UpdateWindow();
}

CMainWindow::~CMainWindow()
{
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_PATCH, &CMainWindow::OnPatch)
	ON_COMMAND(ID_EXIT, &CMainWindow::OnExit)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CMainWindow::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	BITMAP bmpInfo;
	HBITMAP background = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BACKGROUND));
	GetObject(background, sizeof(BITMAP), &bmpInfo);
	this->m_Background = CreatePatternBrush(background);
	DeleteObject(background);

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int centerX = (screenX >> 1) - (bmpInfo.bmWidth >> 1);
	int centerY = (screenY >> 1) - (bmpInfo.bmHeight >> 1);

	cs.dwExStyle = WS_EX_TOPMOST | WS_EX_LAYERED;
	cs.style = WS_VISIBLE | WS_POPUP;
	cs.x = centerX;
	cs.y = centerY;
	cs.cx = bmpInfo.bmWidth;
	cs.cy = bmpInfo.bmHeight;

	cs.lpszClass = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW,
		::LoadCursor(nullptr, IDC_ARROW),
		this->m_Background,
		::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_MAIN))
	);

	return TRUE;
}


void CMainWindow::PostNcDestroy()
{
	this->KillTimer((UINT_PTR)ID_RENDERTIMER);

	if (this->m_Background != nullptr)
		DeleteObject(this->m_Background);

	SAFE_DELETE(this->m_CmdPatch);
	SAFE_DELETE(this->m_CmdExit);
	SAFE_DELETE(this->m_Screen);
}


int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->SetLayeredWindowAttributes(RGB(0, 255, 0), 0, LWA_COLORKEY);

	this->m_Screen->SetTitle("SUFFERMORE");

	this->m_Patcher.Load(this->m_Greenhell.GetDllPath());
	if (!this->m_Greenhell.IsInstalled())
		this->m_Screen->SetText("GAME FILES NOT DETECTED");
	else
		this->m_Screen->SetText("ALLOWS UP TO 8 PEOPLE TO PLAY");

	return 0;
}


void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, NULL);
	CFrameWnd::OnLButtonDown(nFlags, point);
}


void CMainWindow::OnPatch()
{
	if (!this->m_IsPatched)
	{
		if (this->m_Patcher.IsPatched())
		{
			this->m_Screen->SetText("GAME IS ALREADY PATCHED");
			return;
		}

		std::streampos pos;
		if (!this->m_Patcher.Find("1A80????????1780????????73????????80????????2A", &pos, 512))
		{
			this->m_Screen->SetText("ERROR MISSING OPCODES");
			return;
		}

		if (!this->m_Patcher.Patch(pos, "1E"))
		{
			this->m_Screen->SetText("PATCH FAILED");
			return;
		}

		this->m_IsPatched = TRUE;
	}

	this->m_Screen->SetText("GAME IS READY TO PLAY");
}


void CMainWindow::OnExit()
{
	this->DestroyWindow();
}


void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	this->m_Screen->OnRender((HDC)dc);
}


void CMainWindow::OnTimer(UINT_PTR nIDEvent)
{
	if (this->m_Screen->OnFrame())
	{
		const Gdiplus::Rect vp = this->m_Screen->Viewport();
		RECT rect = { vp.X, vp.Y, vp.GetRight(), vp.GetBottom() };
		this->InvalidateRect(&rect, FALSE);
	}

	CFrameWnd::OnTimer(nIDEvent);
}

#include "framework.h"
#include "resource.h"
#include <mmsystem.h>

#include "gh_patch.h"
#include "CMainWindow.h"
#include "../includes/ufmod.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CApp theApp;


CApp::CApp() noexcept :
	m_Token(0)
{
	this->m_pMainWnd = nullptr;
}

BOOL CApp::InitInstance()
{
	CWinApp::InitInstance();

	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&this->m_Token, &input, nullptr);

#ifndef _DEBUG
	uFMOD_SetVolume(13);
	uFMOD_PlaySong(MAKEINTRESOURCE(IDR_MUSIC), this->m_hInstance, XM_RESOURCE);
#endif

	CMainWindow* mainWindow = new CMainWindow();
	if (!mainWindow)
		return FALSE;

	this->m_pMainWnd = mainWindow;

	return TRUE;
}

int CApp::ExitInstance()
{
	SAFE_DELETE(this->m_pMainWnd);

	if (this->m_Token)
		Gdiplus::GdiplusShutdown(this->m_Token);

#ifndef _DEBUG
	uFMOD_StopSong();
#endif

	return CWinApp::ExitInstance();
}

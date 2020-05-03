#pragma once
#ifndef CAPP_H
#define CAPP_H

#include "framework.h"


class CApp : public CWinApp
{
public:
	CApp() noexcept;
	virtual ~CApp() {};

	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:
	DWORD m_Token;
};

extern CApp theApp;


#endif

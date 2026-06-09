#pragma once
#ifndef CAPP_H
#define CAPP_H

#include "framework.h"
#include <string>


class CApp : public CWinApp
{
public:
	CApp() noexcept;
	virtual ~CApp() = default;

	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:
	inline static const std::string MUTEX_NAME = "SUFFER2GETHER_1acbf36d-f973-4aa2-a113-38345f84e17a";
	ULONG_PTR m_Token;
	HANDLE m_Mutex;
};

extern CApp theApp;


#endif

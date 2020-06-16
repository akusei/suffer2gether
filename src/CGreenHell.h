#pragma once
#ifndef CGREENHELL_H
#define CGREENHELL_H


#include "framework.h"
#include "global.h"
#include <string>
#include <filesystem>


class CGreenHell
{
public:
	CGreenHell();
	virtual ~CGreenHell();

	const BOOL IsInstalled();
	const std::filesystem::path& GetDllPath();
	void SetDllPath(const std::filesystem::path& path);
	void SetManualMode();

protected:
	std::filesystem::path m_DllPath;
	BOOL m_Checked;
	BOOL m_IsInstalled;

private:
	const std::string REG_KEY = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Steam App 815370";
};


#endif
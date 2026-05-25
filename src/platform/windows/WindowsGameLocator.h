#pragma once
#ifndef WINDOWSGAMELOCATOR_H
#define WINDOWSGAMELOCATOR_H


#include "framework.h"
#include "../../core/global.h"
#include "../../core/IGameLocator.h"

#include <string>
#include <filesystem>


class WindowsGameLocator
{
public:
	WindowsGameLocator();
	virtual ~WindowsGameLocator();

	const BOOL IsInstalled();
	const std::filesystem::path& GetDllPath();
	std::filesystem::path GetGamePath() override;
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

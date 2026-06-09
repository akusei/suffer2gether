#pragma once
#ifndef GAMELOCATOR_H
#define GAMELOCATOR_H


#include "global.h"
#include "IGameLocator.h"

#include <string>
#include <filesystem>


class GameLocator : public IGameLocator
{
public:
	GameLocator();
	virtual ~GameLocator() = default;

	std::filesystem::path GetGamePath() override;

protected:
	std::filesystem::path m_DllPath;

private:
	inline static const std::string REG_KEY = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Steam App 815370";
};


#endif

#pragma once
#ifndef LINUXGAMELOCATOR_H
#define LINUXGAMELOCATOR_H

#include "../../core/IGameLocator.h"
#include <filesystem>
#include <string>
#include <vector>

class LinuxGameLocator : public IGameLocator
{
public:
    LinuxGameLocator() = default;
    virtual ~LinuxGameLocator() = default;

    std::filesystem::path GetGamePath() override;
};

#endif

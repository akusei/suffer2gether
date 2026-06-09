#pragma once
#ifndef GAMELOCATOR_H
#define GAMELOCATOR_H

#include "IGameLocator.h"
#include <filesystem>


class GameLocator : public IGameLocator
{
public:
    GameLocator() = default;
    virtual ~GameLocator() = default;

    std::filesystem::path GetGamePath() override;
};


#endif

#pragma once
#include <string>
#define IGAMELOCATOR_H
#include <filesystem>
#include <string>


class IGameLocator {
public:
    virtual ~IGameLocator() = default;

    // 0 means: "Any class that claims to be an IGameLocator MUST write a GetGamePath function."
    virtual std::filesystem::path GetGamePath() = 0;
};

#include "../../core/CPatcher.h"
#include "../../platform/linux/LinuxGameLocator.h"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[])
{
    std::filesystem::path targetPath;

    // Check if the user passed a path via the command line
    if (argc >= 2)
    {
        targetPath = argv[1];
        std::cout << "Using provided path: " << targetPath << "\n";
    }
    // Fallback: If no path was provided, try to find it automatically
    else
    {
        std::cout << "No path provided. Searching for Green Hell...\n";
        LinuxGameLocator locator;
        targetPath = locator.GetGamePath();

        if (targetPath.empty())
        {
            std::cout << "Error: Could not auto-detect Green Hell installation.\n";
            std::cout << "Please provide the path manually:\n";
            std::cout << "Usage: ./suffer2gether <path_to_Assembly-CSharp.dll>\n";
            return 1;
        }

        std::cout << "Auto-detected game at: " << targetPath << "\n";
    }

    CPatcher patcher;

    if (!patcher.Load(targetPath))
    {
        std::cout << "Failed to load: " << patcher.GetLastError() << "\n";
        return 1;
    }

    if (patcher.IsPatched())
    {
        std::cout << "Game is already patched!\n";
        return 0;
    }

    std::streampos pos;
    if (!patcher.Find("1A80????????1780????????73????????80????????2A", &pos))
    {
        std::cout << "Error: Missing opcodes. Is the game already updated?\n";
        return 1;
    }

    if (!patcher.Patch(pos, "1E"))
    {
        std::cout << "Patch failed!\n";
        return 1;
    }

    std::cout << "SUFFERMORE: Game successfully patched for 8 players!\n";
    return 0;
}

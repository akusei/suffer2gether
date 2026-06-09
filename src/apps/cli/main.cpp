#include "global.h"
#include "CPatcher.h"
#include "GameLocator.h"

#include <iostream>
#include <filesystem>


int main(int argc, char* argv[])
{
    std::filesystem::path targetPath;

    // Check if the user passed a path via the command line
    if (argc >= 2)
    {
        targetPath = std::filesystem::path(argv[1]) / "GH_Data" / "Managed" / "Assembly-CSharp.dll";
        std::cout << "Using provided path: \"" << targetPath.string() << "\"\n";
    }
    // Fallback: If no path was provided, try to find it automatically
    else
    {
        std::cout << "No path provided. Searching for Green Hell...\n";

        GameLocator locator;
        targetPath = locator.GetGamePath();

        if (targetPath.empty())
        {
            std::cout << "Error: Could not auto-detect Green Hell installation.\n";
            std::cout << "Please provide the path manually:\n";
            std::cout << "Usage: suffer2gether <path_to_Assembly-CSharp.dll>\n";
            return 1;
        }

        std::cout << "Auto-detected game at: \"" << targetPath.string() << "\"\n";
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
    if (!patcher.Find(BYTE_PATTERN, &pos, 512))
    {
        std::cout << "Error: Missing opcodes. Is the game already updated?\n";
        return 1;
    }

    if (!patcher.Patch(pos, BYTE_REPLACEMENT))
    {
        std::cout << "Patch failed!\n";
        return 1;
    }

    std::cout << "SUFFERMORE: Game successfully patched for 8 players!\n";
    return 0;
}

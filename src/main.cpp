#include "CPatcher.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./suffer2gether <path_to_Assembly-CSharp.dll>\n";
        return 1;
    }

    CPatcher patcher;
    // Load the file passed via the terminal argument
    if (!patcher.Load(argv[1])) {
        std::cout << "Failed to load: " << patcher.GetLastError() << "\n";
        return 1;
    }

    if (patcher.IsPatched()) {
        std::cout << "Game is already patched!\n";
        return 0;
    }

    // Exact byte pattern from the original CMainWindow.cpp
    std::streampos pos;
    if (!patcher.Find("1A80????????1780????????73????????80????????2A", &pos)) {
        std::cout << "Error: Missing opcodes. Is the game already updated?\n";
        return 1;
    }

    if (!patcher.Patch(pos, "1E")) {
        std::cout << "Patch failed!\n";
        return 1;
    }

    std::cout << "SUFFERMORE: Game successfully patched for 8 players!\n";
    return 0;
}

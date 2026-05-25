#include "LinuxGameLocator.h"
#include <cstdlib>
#include <filesystem>

using namespace std;

std::filesystem::path LinuxGameLocator::GetGamePath()
{
	// Get the user's home directory (e.g., /home/username)
	const char* homeDir = std::getenv("HOME");
	if (homeDir == nullptr)
		return filesystem::path();

	string home(homeDir);

	// Common default Steam library paths on Linux
	vector<string> possiblePaths = {
		home + "/.local/share/Steam/steamapps/common/Green Hell/GH_Data/Managed/Assembly-CSharp.dll",
		home + "/.steam/steam/steamapps/common/Green Hell/GH_Data/Managed/Assembly-CSharp.dll",
		home + "/games/steam/steamapps/common/Green Hell/GH_Data/Managed/Assembly-CSharp.dll"
	};

	// Check if the file exists in any of the common locations
	for (const auto& pathStr : possiblePaths)
	{
		filesystem::path p(pathStr);
		if (filesystem::exists(p))
		{
			return p;
		}
	}

	// Return empty path if not found
	return filesystem::path();
}

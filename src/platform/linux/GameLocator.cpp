#include "GameLocator.h"
#include <filesystem>
#include <vector>

using namespace std;


filesystem::path GameLocator::GetGamePath()
{
	// Get the user's home directory (e.g., /home/username)
	const char* homeDir = std::getenv("HOME");

	if (homeDir == nullptr)
		return filesystem::path();

	filesystem::path home(homeDir);

	// Common default Steam library paths on Linux
	vector<filesystem::path> possiblePaths = {
		home / ".local/share/Steam/steamapps/common/Green Hell",
		home / ".steam/steam/steamapps/common/Green Hell",
		home / "games/steam/steamapps/common/Green Hell"
	};

	// Check if the file exists in any of the common locations
	for (const auto& basePath : possiblePaths)
	{
		filesystem::path targetFile = basePath / "GH_Data" / "Managed" / "Assembly-CSharp.dll";
		if (filesystem::exists(targetFile))
		{
			return basePath;
		}
	}

	// Return empty path if not found
	return filesystem::path();
}

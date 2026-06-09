#include "GameLocator.h"
#include "framework.h"

using namespace std;


GameLocator::GameLocator() :
	m_DllPath(filesystem::path())
{
}

std::filesystem::path GameLocator::GetGamePath()
{
	if (!this->m_DllPath.empty())
		return this->m_DllPath;

	HKEY key;
	const char* regKey = this->REG_KEY.c_str();

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, KEY_QUERY_VALUE | KEY_WOW64_32KEY, &key) != ERROR_SUCCESS)
			return filesystem::path();
	}

	DWORD size = MAX_PATH;
	DWORD type = REG_SZ;
	char path[MAX_PATH]{};

	if (RegQueryValueEx(key, "InstallLocation", nullptr, (LPDWORD)&type, (LPBYTE)&path, (LPDWORD)&size) == ERROR_SUCCESS)
	{
		filesystem::path dllPath = filesystem::path(path) / "GH_Data" / "Managed" / "Assembly-CSharp.dll";
		if (filesystem::exists(dllPath))
			this->m_DllPath = dllPath;
	}

	RegCloseKey(key);

	return this->m_DllPath;
}

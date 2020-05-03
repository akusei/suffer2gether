#include "CGreenHell.h"

using namespace std;


CGreenHell::CGreenHell() : 
	m_Checked(FALSE), 
	m_DllPath(filesystem::path()), 
	m_IsInstalled(FALSE)
{
}

CGreenHell::~CGreenHell()
{

}

const BOOL CGreenHell::IsInstalled()
{
	if (this->m_Checked)
		return this->m_IsInstalled;

	HKEY key;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, this->REG_KEY.c_str(), 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, this->REG_KEY.c_str(), 0, KEY_QUERY_VALUE | KEY_WOW64_32KEY, &key) != ERROR_SUCCESS)
		{
			this->m_IsInstalled = FALSE;
			this->m_Checked = TRUE;
			return FALSE;
		}
	}

	if (this->m_DllPath.empty())
	{
		DWORD size = MAX_PATH;
		DWORD type = REG_SZ;
		char path[MAX_PATH];
		if (RegQueryValueEx(key, "InstallLocation", nullptr, (LPDWORD)&type, (LPBYTE)&path, (LPDWORD)&size) == ERROR_SUCCESS)
		{
			filesystem::path dllPath = filesystem::path(path)
				.append("GH_Data")
				.append("Managed")
				.append("Assembly-CSharp.dll");
			if (filesystem::exists(dllPath))
				this->m_DllPath = dllPath;
		}
	}

	RegCloseKey(key);

	this->m_IsInstalled = !this->m_DllPath.empty();
	this->m_Checked = TRUE;

	return this->m_IsInstalled;
}

const filesystem::path& CGreenHell::GetDllPath()
{
	if (!this->m_Checked)
		this->IsInstalled();

	return this->m_DllPath;
}
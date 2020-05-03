#pragma once
#ifndef PATCHER_H
#define PATCHER_H

#include "framework.h"
#include "global.h"
#include <filesystem>
#include <fstream>
#include <vector>


class CPatcher
{
public:
	CPatcher();
	virtual ~CPatcher();

	BOOL Load(const std::filesystem::path& filename, DWORD startingOffset = 0);
	BOOL Find(const std::string& pattern, std::streampos* offset, DWORD startingOffset = 0, DWORD seekDir = std::ios::beg);

	BOOL Patch(std::streampos offset, const std::string& pattern);
	BOOL IsPatched();

	const std::string& GetLastError() const;

protected:
	const DWORD CHUNK_SIZE = 4096;

	std::filesystem::path m_Filename;
	std::fstream m_File;
	BYTE* m_Buffer;
	DWORD m_DataSize;
	std::string m_LastError;

private:
	const BYTE WILDCARD = '?';
	const DWORD PATCH_MAGIC = 0xDEADC0DE;
	const DWORD MAGIC_OFFSET = 0x88;
	typedef struct Pattern {
		BYTE High;
		BYTE Low;
	} Pattern;

	BYTE ToByte(const char ch) const;
	std::vector<Pattern> ParsePattern(const std::string& pattern) const;
};


#endif

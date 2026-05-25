#pragma once
#ifndef PATCHER_H
#define PATCHER_H

#include "global.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstdint>

class CPatcher
{
public:
	CPatcher();
	virtual ~CPatcher();

	bool Load(const std::filesystem::path& filename, uint32_t startingOffset = 0);
	bool Find(const std::string& pattern, std::streampos* offset, uint32_t startingOffset = 0, std::ios::seekdir seekDir =std::ios::beg);

	bool Patch(std::streampos offset, const std::string& pattern);
	bool IsPatched();

	const std::string& GetLastError() const;

protected:
	const uint32_t CHUNK_SIZE = 4096;

	std::filesystem::path m_Filename;
	std::fstream m_File;
	uint8_t* m_Buffer;
	uint32_t m_DataSize;
	std::string m_LastError;

private:
	const uint8_t WILDCARD = '?';
	const uint32_t PATCH_MAGIC = 0xDEADC0DE;
	const uint32_t MAGIC_OFFSET = 0x88;
	typedef struct Pattern {
		uint8_t High;
		uint8_t Low;
	} Pattern;

	uint8_t ToByte(const char ch) const;
	std::vector<Pattern> ParsePattern(const std::string& pattern) const;
};


#endif

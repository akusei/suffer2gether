#include "CPatcher.h"

using namespace std;


CPatcher::CPatcher() : 
	m_Buffer(new BYTE[CHUNK_SIZE]),
	m_File(),
	m_Filename(),
	m_DataSize(0),
	m_LastError()
{
}

CPatcher::~CPatcher()
{
	delete[] this->m_Buffer;
	this->m_File.close();
}

BOOL CPatcher::Load(const filesystem::path& filename, DWORD startingOffset)
{
	this->m_File.close();
	this->m_File.open(filename, ios::in | ios::out | ios::binary, _SH_DENYWR);
	if (!this->m_File.is_open())
	{
		this->m_LastError = "Unable to open file";
		return FALSE;
	}

	this->m_LastError.clear();

	return TRUE;
}

BOOL CPatcher::Find(const string& pattern, streampos* offset, DWORD startingOffset, DWORD seekDir)
{
	this->m_LastError.clear();
	if (!this->m_File.is_open())
	{
		this->m_LastError = "file is not open";
		return FALSE;
	}

	this->m_File.seekg(startingOffset, seekDir);
	int backOffset = -(int)((pattern.length() >> 1) - 1);

	vector<CPatcher::Pattern> binPattern = this->ParsePattern(pattern);

	BOOL fullMatch = FALSE;
	streampos foundOffset;
	int delta;

	while (this->m_File.read((char*)this->m_Buffer, this->CHUNK_SIZE) && !fullMatch)
	{
		this->m_DataSize = this->m_File.gcount();
		foundOffset = this->m_File.tellg() - (streampos)this->m_DataSize;
		delta = -1;

		for (int i = 0; i < this->m_DataSize && !fullMatch; i++, delta++)
		{
			fullMatch = TRUE;
			for (int j = 0; j < binPattern.size(); j++)
			{
				BYTE byte = this->m_Buffer[i + j];
				BYTE high = binPattern[j].High;
				BYTE low = binPattern[j].Low;

				if (high != this->WILDCARD && (byte >> 4) != high)
				{
					fullMatch = FALSE;
					break;
				}

				if (low != this->WILDCARD && (byte & 0x0f) != low)
				{
					fullMatch = FALSE;
					break;
				}
			}
		}

		this->m_File.seekg(backOffset, ios::cur);
	}

	if (offset != nullptr && fullMatch)
		*offset = foundOffset + (streampos)delta;

	return fullMatch;
}

BOOL CPatcher::Patch(streampos offset, const string& pattern)
{
	streampos oldPos = this->m_File.tellp();
	this->m_File.seekg(offset, ios::beg);
	vector<CPatcher::Pattern> binPattern = this->ParsePattern(pattern);

	DWORD size = binPattern.size();
	BYTE* buffer = new BYTE[size];
	this->m_File.read((char*)buffer, size);

	for (int i = 0; i < size; i++)
	{
		BYTE byte = buffer[i];
		BYTE high = binPattern[i].High;
		BYTE low = binPattern[i].Low;

		if (high != this->WILDCARD && (byte >> 4) != high)
			buffer[i] = (buffer[i] & 0x0f) | (high << 4);

		if (low != this->WILDCARD && (byte & 0x0f) != low)
			buffer[i] = (buffer[i] & 0xf0) | low;
	}

	this->m_File.seekp(offset, ios::beg);
	this->m_File.write((char*)buffer, size);

	delete[] buffer;

	this->m_File.seekp(this->MAGIC_OFFSET, ios::beg);
	this->m_File.write((char*)&this->PATCH_MAGIC, sizeof(DWORD));

	this->m_File.seekp(oldPos, ios::beg);
	this->m_File.flush();

	return TRUE;
}

BOOL CPatcher::IsPatched()
{
	streampos oldPos = this->m_File.tellg();
	this->m_File.seekg(this->MAGIC_OFFSET, ios::beg);

	DWORD data;
	this->m_File.read((char*)&data, sizeof(DWORD));
	this->m_File.seekg(oldPos, ios::beg);

	return (data == this->PATCH_MAGIC);
}

BYTE CPatcher::ToByte(const char ch) const
{
	BYTE value = this->WILDCARD;

	if (ch >= '0' && ch <= '9')
		value = ch - '0';
	else if (ch >= 'A' && ch <= 'F')
		value = ch - 0x37;

	return value;
}

vector<CPatcher::Pattern> CPatcher::ParsePattern(const string& pattern) const
{
	vector<CPatcher::Pattern> patterns;
	for (int i = 0; i < pattern.length(); i += 2)
	{
		BYTE high = this->ToByte(pattern.at(i));
		BYTE low = this->ToByte(pattern.at(i + 1));
		patterns.push_back({ high, low });
	}

	return patterns;
}

const string& CPatcher::GetLastError() const
{
	return this->m_LastError;
}
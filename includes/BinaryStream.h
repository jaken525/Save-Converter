#ifndef BINERYSTREAM_H
#define BINERYSTREAM_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <shlwapi.h>

class BinaryStream
{
private:
	size_t fileSize = 0;
	size_t pos = 0;

	bool isFileOpen;

public:
	char* buffer = NULL;

	BinaryStream()
	{
		buffer = NULL;

		fileSize = 0;
		pos = 0;

		isFileOpen = false;
	}

	BinaryStream(std::string fileName)
	{
		isFileOpen = OpenFile(fileName);

		if (!isFileOpen)
			throw "Failed to Open File\n";
	}

	~BinaryStream()
	{
		Clear();
	}

	unsigned int ReadShortShort();
	unsigned short ReadShort();
	unsigned long ReadLong();
	float ReadFloat();
	std::string ReadStringWithoutZeroes(int size);
	std::string ReadString(int size);
	bool Jump(int jump);

	std::string WriteString(int size, std::string str);
	std::string WriteShort(int num);
	std::string WriteFloat(float num);
	std::string WriteLong(int num);

	bool OpenFile(std::string filename);
	void Clear();
	std::string GetFileNamePath(const std::string str);
	std::string GetFilenameFile(const std::string str);

	char* GetBuffer() { return buffer; }
	int* GetIntBuffer()
	{
		int* intBuffer = new int[fileSize];

		for (int i = 0; i < fileSize; ++i)
			intBuffer[i] = buffer[i] - '0';

		return intBuffer;
	}

	void PrintFile();
	size_t GetPosition()
	{
		return pos;
	}
};

#endif
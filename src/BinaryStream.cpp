#include "../includes/BinaryStream.h"

void BinaryStream::Clear()
{
	this->pos = 0;
	this->fileSize = 0;
	if (buffer = NULL) delete[] this->buffer;
}

bool BinaryStream::OpenFile(std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
	);

	Clear();
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to Open File\n";
		return false;
	}

	this->fileSize = GetFileSize(hFile, NULL);
	if (this->fileSize == 0)
	{
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
	}

	this->buffer = new char[this->fileSize];
	unsigned long dwBytesRead = 0;
	if (ReadFile(hFile, this->buffer, this->fileSize, &dwBytesRead, NULL) == FALSE || dwBytesRead != this->fileSize)
	{
		std::cout << "Failed to copy file into memory\n";

		this->fileSize = 0;
		delete[] this->buffer;
		this->buffer = NULL;

		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

std::string BinaryStream::WriteLong(int num)
{
	std::string Hex = "";
	std::stringstream s;
	s << std::hex << num;

	int zeroes = 8 - size(s.str());
	for (int i = 0; i < zeroes; i++)
		Hex += "0";
	Hex += s.str();

	int arr[] = { 0, 0, 0, 0 };
	int c = 3;
	for (int i = 0; i < Hex.length() - 1; i += 2)
	{
		std::stringstream h;
		h << Hex[i] << Hex[i + 1];
		h >> std::hex >> arr[c];
		c--;
	}

	Hex = "";
	for (int i = 0; i < 4; i++)
		Hex += char(uint8_t(arr[i]));

	return Hex;
}

std::string BinaryStream::WriteFloat(float num)
{
	std::string strHEX = "";
	unsigned long a = 0;
	unsigned long a24 = 0;
	float n = num;

	memcpy(&a, &n, 4);
	strHEX += char(uint8_t(a));
	strHEX += char((uint16_t(a) - uint8_t(a)) / 0x00000100);

	memcpy(&a24, &n, 3);
	strHEX += char((a24 - int(uint16_t(a))) / 0x00010000);
	strHEX += char((a - a24) / 0x01000000);

	return strHEX;
}

std::string BinaryStream::WriteShort(int num)
{
	int arr[] = { 0, 0 };
	while (num >= 256)
	{
		arr[1] += 1;
		num -= 256;
	}
	arr[0] = num;

	std::string hex;
	for (int i = 0; i < 2; i++)
		hex += char(arr[i]);

	return hex;
}

std::string BinaryStream::WriteString(int size, std::string str)
{
	size -= str.length();

	std::string endLine = "";
	endLine += str;

	for (int i = 0; i < size; i++)
		endLine += char(uint8_t(0));

	return endLine;
}

bool BinaryStream::Jump(int jump)
{
	pos += jump;
	return true;
}

std::string BinaryStream::ReadString(int size)
{
	std::string result = "";

	for (int i = 0; i < size; i++)
	{
		result += this->buffer[pos];
		pos += 1;
	}

	return result;
}

std::string BinaryStream::ReadStringWithoutZeroes(int size)
{
	std::string result = "";
	bool isWriting = true;

	for (int i = 0; i < size; i++)
	{
		if (this->buffer[pos] != 0 && isWriting)
			result += this->buffer[pos];
		else
			isWriting = false;
		pos += 1;
	}

	return result;
}

float BinaryStream::ReadFloat()
{
	float result = 0.0;
	unsigned long b = ReadLong();
	memcpy(&result, &b, 4);

	return result;
}

unsigned long BinaryStream::ReadLong()
{
	unsigned long result = {
		(unsigned int)((uint8_t)this->buffer[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)this->buffer[pos + 1] * 0x00000100) + \
		(unsigned int)((uint8_t)this->buffer[pos + 2] * 0x00010000) + \
		(unsigned int)((uint8_t)this->buffer[pos + 3] * 0x01000000)
	};

	pos += 4;
	return result;
}

unsigned int BinaryStream::ReadShortShort()
{
	unsigned short result = {
		(unsigned int)((uint8_t)this->buffer[this->pos] * 0x00000001)
	};
	pos += 1;
	return result;
}

unsigned short BinaryStream::ReadShort()
{
	unsigned short result = {
		(unsigned int)((uint8_t)this->buffer[this->pos] * 0x00000001) + \
		(unsigned int)((uint8_t)this->buffer[this->pos + 1] * 0x00000100)
	};

	pos += 2;
	return result;
}

std::string BinaryStream::GetFilenameFile(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");

	if (found < str.size())
	{
		strt = str.substr(found + 1, -1);
		found = strt.find(".");

		if (found < strt.size())
			strt = strt.substr(0, found);
	}
	else
		strt = str;

	size_t lastdot = strt.find_last_of(".");
	if (lastdot == std::string::npos)
		return strt;

	return strt.substr(0, lastdot);
}

std::string BinaryStream::GetFileNamePath(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");

	if (found != std::string::npos)
	{
		strt = str.substr(0, found);

		return (strt + "\\");
	}
	else
		return "";
}

void BinaryStream::PrintFile()
{
	for (int i = 0; i < fileSize; i++)
		if (i % 16 == 0)
		{

		}
}
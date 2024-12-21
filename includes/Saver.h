#ifndef MYSAVER_H
#define MYSAVER_H
#include "SaveParser.h"
#include "Crypt.h"

class SaveConverter
{
public:
	SaveConverter() {};
	~SaveConverter() {};

	SaveConverter(std::string path)
	{
		this->path = path;
	}

	void OpenProfile();

private:
	SaveParser parser;

	std::string path = "";
	std::string profileName = "";

	void Convert();
};

#endif
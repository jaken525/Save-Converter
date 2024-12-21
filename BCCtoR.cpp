#include "./includes/Saver.h"

std::string currentPath = "";

int main(int* argc, char* argv[])
{
	currentPath = std::filesystem::current_path().string();
	std::string file = "";
	if (argv[1] == NULL)
		file = OpenFilename();
	else
		file = argv[1];

	std::cout << "Opening " << file << "...\n\n";

	if (file != "")
	{
		SaveConverter converter(file);
		converter.OpenProfile();
	}

	system("pause");
    return 0;
}
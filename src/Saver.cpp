#include "../includes/Saver.h"

void SaveConverter::OpenProfile()
{
	if (!parser.LoadProfile(path))
	{
		std::cout << "Save loading failed!" << std::endl;
		return;
	}

	Convert();
}

void SaveConverter::Convert()
{
    std::vector<int> modes { 2, 0, 1, 4, 3, 6, 5 };

    std::vector<std::string> jump
    {
        "bcjump1_l ",
        "bcjump2_l ",
        "bcjump3_l ",
        "bcjump4_l ",
        "bcjumpwbc_l ",
        "qrjump_l "
    };

    std::map<Map, std::string> maps
    {
        { Map(6, 8), "qrcross" },
        { Map(1, 4), "qrspeed" },
        { Map(7, 7), "qrbuggy" },
        { Map(5, 6), "qrmonster" },
        { Map(5, 0), "bcmonster1" },
        { Map(5, 1), "bcmonster2" },
        { Map(5, 2), "bcmonster3" },
        { Map(5, 3), "bcmonster4" },
        { Map(5, 4), "bcmonsterwbc" },
        { Map(6, 0), "bccross1" },
        { Map(6, 2), "bccross2" },
        { Map(6, 1), "bccross3" },
        { Map(6, 3), "bccross4" },
        { Map(6, 4), "bccrosswbc" },
	    { Map(2, 4), "bcspeedfc" },
        { Map(2, 0), "bcspeed1" },
        { Map(1, 0), "bcspeed2" },
        { Map(1, 1), "bcspeed3" },
        { Map(3, 0), "bcspeed4" },
        { Map(2, 1), "bcspeedwbc" },
        { Map(7, 1), "bcbuggy1" },
        { Map(7, 0), "bcbuggy2" },
        { Map(7, 2), "bcbuggy3" },
        { Map(7, 3), "bcbuggy4" },
        { Map(7, 4), "bcbuggywbc" },
        { Map(3, 1), "bcbspeed1" },
        { Map(7, 5), "bcbbuggy2" },
        { Map(5, 5), "bcbbuggy1" },
        { Map(5, 7), "bcbmonster1" },
        { Map(1, 4), "urockr" },
        { Map(1, 4), "urockr1" },
        { Map(1, 4), "urockrn" },
        { Map(6, 8), "cnrsqrr" },
        { Map(7, 0), "sharkbeatnr" },
        { Map(2, 0), "snakealleyr" },
        { Map(7, 7), "buggybeat" },
        { Map(6, 0), "cnrdaylightr" },
        { Map(6, 1), "cnrrainr" },
    };

    std::vector<std::string> records
    {
        "qrderby_l 12548",
	    "bcderby1_l 10284",
	    "bcderby2_l 6248",
	    "bcderby3_l 10987",
	    "bcderby4_l 2630",
	    "bcderbywbc_l 11264",
        "sandsofrage_l 004539",
        "sandsofrage_t 021896",
    };

    std::map<Car, int> allCars
    {
        { Car(0, 0), 12 },
        { Car(0, 1), 13 },
        { Car(0, 2), 14 },
        { Car(0, 3), 15 },
        { Car(1, 0), 37 },
        { Car(1, 1), 38 },
        { Car(1, 2), 39 },
        { Car(1, 3), 40 },
        { Car(2, 0), 29 },
        { Car(2, 1), 30 },
        { Car(2, 2), 31 },
        { Car(2, 3), 32 },
        { Car(3, 0), 46 },
        { Car(3, 1), 47 },
        { Car(4, 0), 9 },
        { Car(4, 1), 10 },
        { Car(5, 0), 55 },
        { Car(5, 1), 56 },
        { Car(5, 2), 57 },
        { Car(5, 3), 58 },
        { Car(6, 0), 33 },
        { Car(6, 1), 34 },
        { Car(6, 2), 35 },
        { Car(6, 3), 36 },
        { Car(7, 0), 7 },
        { Car(7, 1), 8 },
        { Car(8, 0), 20 },
        { Car(8, 1), 21 },
        { Car(8, 2), 22 },
        { Car(8, 3), 23 },
        { Car(9, 0), 59 },
        { Car(9, 1), 60 },
        { Car(9, 2), 61 },
        { Car(9, 3), 62 },
        { Car(10, 0), 18 },
        { Car(10, 1), 19 },
        { Car(11, 0), 24 },
        { Car(11, 1), 25 },
        { Car(11, 2), 26 },
        { Car(11, 3), 27 },
        { Car(12, 0), 0 },
        { Car(12, 1), 1 },
        { Car(12, 2), 2 },
        { Car(12, 3), 3 },
        { Car(13, 0), 5 },
        { Car(13, 1), 6 },
        { Car(14, 0), 41 },
        { Car(14, 1), 42 },
        { Car(14, 2), 43 },
        { Car(14, 3), 44 },
        { Car(15, 0), 16 },
        { Car(15, 1), 17 },
    };

	std::string usersPath = currentPath + "\\Users\\";
	std::string profilePath = currentPath + "\\Users\\" + parser.localProfile.profileName + "\\";

	if (!std::filesystem::exists(usersPath))
		std::filesystem::create_directory(usersPath);

	if (!std::filesystem::exists(profilePath))
		std::filesystem::create_directory(profilePath);

    std::ofstream file;

	// passed file
    std::cout << "Converting Passed.dat\n";
	std::string full = "";
	full += std::to_string(parser.localChampionshipProfile.championshipLevels) + "\n";
	for (int i = 0; i < 5; i++)
	{
		std::string line = "";
        line += std::to_string(parser.localProfile.modes[modes[i]].levelPassed[0]);
        for (int j = 1; j < 4; j++)
            line += "," + std::to_string(parser.localProfile.modes[modes[i]].levelPassed[j]);

        full += std::to_string(i) + "-" + line + "\n";
	}
    full += "5-0,0,0,0\n";
    full += "6-" + std::to_string(parser.localProfile.modes[6].levelPassed[0]);
    for (int j = 1; j < 4; j++)
        full += "," + std::to_string(parser.localProfile.modes[6].levelPassed[j]);

    full += "\n7-" + std::to_string(parser.localProfile.modes[5].levelPassed[0]);
    for (int j = 1; j < 5; j++)
        full += "," + std::to_string(parser.localProfile.modes[5].levelPassed[j]);
    full += ",0\n";

    file.open(profilePath + "Passed.dat", std::ios::binary);
    for (auto sym : Crypt::Encrypt(full))
        file << sym;

	file.close();
    std::cout << "Passed.dat converted!\n";

    // Cars file
    std::cout << "Converting Cars.dat\n";
    full = "";
    full += std::to_string((int)parser.localProfile.points) + "\n";
    for (int i = 0; i < 5; i++)
    {
        std::string line = "";
        Car car = Car(parser.localProfile.cars[i].yourCars[0].id, parser.localProfile.cars[i].yourCars[0].color);
        line += std::to_string(allCars[car]);
        for (int j = 1; j < 15; j++)
        {
            car = Car(parser.localProfile.cars[i].yourCars[j].id, parser.localProfile.cars[i].yourCars[j].color);
            if (car.id == 255)
                break;

            line += "," + std::to_string(allCars[car]);
        }

        if (parser.localProfile.openFinalChallenge == 1 && i == 0)
            line += ",54";

        full += std::to_string(i) + "-" + line + "\n";
    }
    full += "5-";

    file.open(profilePath + "Cars.dat", std::ios::binary);
    for (auto sym : Crypt::Encrypt(full))
        file << sym;

    file.close();
    std::cout << "Cars.dat converted!\n";

    // Records file
    std::cout << "Converting Records.dat\n";
    full = "";

    for (int i = 0; i < sizeOfBCModes - 1; i++)
    {
        std::string s = std::to_string(parser.localProfile.jumpDistances[i]);
        std::replace(s.begin(), s.end(), '.', ',');
        full += jump[i] + s + "\n";
    }

    for (int i = 0; i < sizeOfBCModes; i++)
        for (int j = 0; j < 10; j++)
        {
            Map map = Map(i + 1, j);

            if (maps.contains(map))
            {
                std::stringstream totalTime;
                totalTime << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].totalTime[j].minutes)
                    << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].totalTime[j].seconds)
                    << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].totalTime[j].milliseconds);

                std::stringstream lapTime;
                lapTime << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].lapTime[j].minutes)
                    << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].lapTime[j].seconds)
                    << std::setw(2) << std::setfill('0') << std::to_string(parser.recordProfile.levels[i].lapTime[j].milliseconds);

                full += maps[map] + "_l " + lapTime.str() + "\n";
                full += maps[map] + "_t " + totalTime.str() + "\n";
            }
        }

    for (int i = 0; i < records.size(); i++)
    {
        full += records[i];
        if (i != records.size() - 1)
            full += "\n";
    }

    file.open(profilePath + "Records.dat", std::ios::binary);
    for (auto sym : Crypt::Encrypt(full))
        file << sym;

    file.close();
    std::cout << "Records.dat converted!\n\n";
}

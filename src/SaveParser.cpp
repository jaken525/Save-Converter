#include "../includes/SaveParser.h"

std::string OpenFilename()
{
	std::string filename(MAX_PATH, '\0');
	OPENFILENAME ofn = { };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Beetle Crazy Cup User File (*.usr)\0*.usr\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = &filename[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	if (!GetOpenFileName(&ofn))
		return "";
	return filename;
}

std::string GetFilenamePath(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");
	if (found != std::string::npos)
	{
		strt = str.substr(0, found);
		return (strt + "\\");
	}
	else return "";
}

std::string GetFilenameFile(const std::string str)
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
	else strt = str;
	size_t lastdot = strt.find_last_of(".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
}

bool SaveParser::LoadProfile(std::string path)
{
	if (path == "")
	{
		bstream.Clear();
		return false;
	}

	std::string fileName = GetFilenameFile(path);
	std::string filePath = GetFilenamePath(path);

	this->fileName = fileName;
	this->filePath = filePath;

	LoadBCSaveFile(filePath, fileName);
	LoadChampionshipSaveFile(filePath, fileName);
	LoadRecordsSaveFile(filePath, fileName);

	bstream.Clear();
	return true;
}

void SaveParser::LoadChampionshipSaveFile(std::string filePath, std::string fileName)
{
	if (bstream.OpenFile(filePath + fileName + "\\Camp.r-b"))
	{
		localChampionshipProfile.saveVersion = bstream.ReadStringWithoutZeroes(4);

		localChampionshipProfile.profileName = fileName;

		localChampionshipProfile.saveName = bstream.ReadStringWithoutZeroes(32);
		localChampionshipProfile.saveProfileName = bstream.ReadStringWithoutZeroes(32);
		localChampionshipProfile.saveDate = bstream.ReadStringWithoutZeroes(32);

		localChampionshipProfile.points = bstream.ReadFloat();

		localChampionshipProfile.passedTrials = bstream.ReadShortShort();
		localChampionshipProfile.countOfOpenBonus = bstream.ReadShortShort();
		localChampionshipProfile.timeAttackSeconds = bstream.ReadShortShort();
		localChampionshipProfile.championshipLevels = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfBCModes - 1; i++)
			localChampionshipProfile.jumpDistances[i] = bstream.ReadFloat();

		localChampionshipProfile.countOfSaves = bstream.ReadLong();
		localChampionshipProfile.openFinalChallenge = bstream.ReadLong();

		bstream.Jump(128);

		for (int i = 0; i < sizeOfBCModes; i++)
		{
			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].moneyForLevelPassing[j] = bstream.ReadLong();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].moneyForRecordPassing[j] = bstream.ReadLong();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].levelPassed[j] = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].maps[j].id = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].maps[j].level = bstream.ReadShortShort();

			for (int k = 0; k < sizeOfModes; k++)
				for (int j = 0; j < sizeOfModeCars; j++)
					localChampionshipProfile.modes[i].opponentCar[k].carModes[j].color = bstream.ReadShortShort();

			for (int k = 0; k < sizeOfModes; k++)
				for (int j = 0; j < sizeOfModeCars; j++)
					localChampionshipProfile.modes[i].opponentCar[k].carModes[j].id = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].laps[j] = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localChampionshipProfile.modes[i].countOfRacers[j] = bstream.ReadShortShort();

			if (i == sizeOfBCModes - 1)
				bstream.Jump(23);
			else
				bstream.Jump(43);
		}

		localChampionshipProfile.lastMap.id = bstream.ReadShortShort();
		localChampionshipProfile.lastMap.level = bstream.ReadShortShort();
		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.countOfCarsYouHaveInModes[i] = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.countOfCarsYouHaveInQuickRaceMode[i] = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.countOfCarsYouCanBuy[i] = bstream.ReadShortShort();
		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.countOfCarsYouHaveInBonus[i] = bstream.ReadShortShort();

		bstream.Jump(5);

		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.currentCarInModes[i] = bstream.ReadShortShort();
		bstream.Jump(16);
		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.currentCarInBonus[i] = bstream.ReadShortShort();
		bstream.Jump(9);
		for (int i = 0; i < sizeOfModes; i++)
			localChampionshipProfile.currentCarInMarket[i] = bstream.ReadShortShort();
		bstream.Jump(2);

		for (int i = 0; i < sizeOfModes; i++)
		{
			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localChampionshipProfile.cars[i].yourCars[j].id = bstream.ReadShortShort();
				localChampionshipProfile.cars[i].yourCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localChampionshipProfile.cars[i].quickRaceCars[j].id = bstream.ReadShortShort();
				localChampionshipProfile.cars[i].quickRaceCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localChampionshipProfile.cars[i].marketCars[j].id = bstream.ReadShortShort();
				localChampionshipProfile.cars[i].marketCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localChampionshipProfile.cars[i].bonusCars[j].id = bstream.ReadShortShort();
				localChampionshipProfile.cars[i].bonusCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localChampionshipProfile.cars[i].activatedCars[j].id = bstream.ReadShortShort();
				localChampionshipProfile.cars[i].activatedCars[j].color = bstream.ReadShortShort();
			}
		}
	}
}

void SaveParser::LoadBCSaveFile(std::string filePath, std::string fileName)
{
	if (bstream.OpenFile(filePath + fileName + "\\SAVE 01.rb"))
	{
		localProfile.saveVersion = bstream.ReadStringWithoutZeroes(4);

		localProfile.profileName = fileName;

		localProfile.saveName = bstream.ReadStringWithoutZeroes(32);
		localProfile.saveProfileName = bstream.ReadStringWithoutZeroes(32);
		localProfile.saveDate = bstream.ReadStringWithoutZeroes(32);

		localProfile.points = bstream.ReadFloat();

		localProfile.passedTrials = bstream.ReadShortShort();
		localProfile.countOfOpenBonus = bstream.ReadShortShort();
		localProfile.timeAttackSeconds = bstream.ReadShortShort();
		localProfile.championshipLevels = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfBCModes - 1; i++)
			localProfile.jumpDistances[i] = bstream.ReadFloat();

		localProfile.countOfSaves = bstream.ReadLong();
		localProfile.openFinalChallenge = bstream.ReadLong();

		bstream.Jump(128);

		for (int i = 0; i < sizeOfBCModes; i++)
		{
			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].moneyForLevelPassing[j] = bstream.ReadLong();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].moneyForRecordPassing[j] = bstream.ReadLong();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].levelPassed[j] = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].maps[j].id = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].maps[j].level = bstream.ReadShortShort();

			for (int k = 0; k < sizeOfModes; k++)
				for (int j = 0; j < sizeOfModeCars; j++)
					localProfile.modes[i].opponentCar[k].carModes[j].color = bstream.ReadShortShort();
				
			for (int k = 0; k < sizeOfModes; k++)
				for (int j = 0; j < sizeOfModeCars; j++)
					localProfile.modes[i].opponentCar[k].carModes[j].id = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].laps[j] = bstream.ReadShortShort();

			for (int j = 0; j < sizeOfModes; j++)
				localProfile.modes[i].countOfRacers[j] = bstream.ReadShortShort();

			if (i + 1 == sizeOfBCModes)
				bstream.Jump(23);
			else
				bstream.Jump(43);
		}

		localProfile.lastMap.id = bstream.ReadShortShort();
		localProfile.lastMap.level = bstream.ReadShortShort();
		for (int i = 0; i < sizeOfModes; i++)
			localProfile.countOfCarsYouHaveInModes[i] = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfModes; i++)
			localProfile.countOfCarsYouHaveInQuickRaceMode[i] = bstream.ReadShortShort();

		for (int i = 0; i < sizeOfModes; i++)
			localProfile.countOfCarsYouCanBuy[i] = bstream.ReadShortShort();
		for (int i = 0; i < sizeOfModes; i++)
			localProfile.countOfCarsYouHaveInBonus[i] = bstream.ReadShortShort();

		bstream.Jump(5);

		for (int i = 0; i < sizeOfModes; i++)
			localProfile.currentCarInModes[i] = bstream.ReadShortShort();
		bstream.Jump(16);
		for (int i = 0; i < sizeOfModes; i++)
			localProfile.currentCarInBonus[i] = bstream.ReadShortShort();
		bstream.Jump(9);
		for (int i = 0; i < sizeOfModes; i++)
			localProfile.currentCarInMarket[i] = bstream.ReadShortShort();
		bstream.Jump(2);

		for (int i = 0; i < sizeOfModes; i++)
		{
			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localProfile.cars[i].yourCars[j].id = bstream.ReadShortShort();
				localProfile.cars[i].yourCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localProfile.cars[i].quickRaceCars[j].id = bstream.ReadShortShort();
				localProfile.cars[i].quickRaceCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localProfile.cars[i].marketCars[j].id = bstream.ReadShortShort();
				localProfile.cars[i].marketCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localProfile.cars[i].bonusCars[j].id = bstream.ReadShortShort();
				localProfile.cars[i].bonusCars[j].color = bstream.ReadShortShort();
			}

			for (int j = 0; j < sizeOfPlayerCars; j++)
			{
				localProfile.cars[i].activatedCars[j].id = bstream.ReadShortShort();
				localProfile.cars[i].activatedCars[j].color = bstream.ReadShortShort();
			}
		}
	}
}

void SaveParser::LoadRecordsSaveFile(std::string filePath, std::string fileName)
{
	if (bstream.OpenFile(filePath + fileName + "\\records.dat"))
	{
		recordProfile.saveVersion = bstream.ReadStringWithoutZeroes(4);

		bstream.Jump(590);

		for (int i = 0; i < sizeOfBCModes; i++)
			for (int j = 0; j < 10; j++)
			{
				recordProfile.levels[i].totalTime[j].minutes = bstream.ReadShortShort();
				recordProfile.levels[i].totalTime[j].seconds = bstream.ReadShortShort();
				recordProfile.levels[i].totalTime[j].milliseconds = bstream.ReadShortShort();
			}

		bstream.Jump(87);

		for (int i = 0; i < sizeOfBCModes; i++)
			for (int j = 0; j < 10; j++)
			{
				recordProfile.levels[i].lapTime[j].minutes = bstream.ReadShortShort();
				recordProfile.levels[i].lapTime[j].seconds = bstream.ReadShortShort();
				recordProfile.levels[i].lapTime[j].milliseconds = bstream.ReadShortShort();
			}

		bstream.Jump(257);

		for (int i = 0; i < sizeOfBCModes; i++)
			for (int j = 0; j < 10; j++)
				recordProfile.levels[i].playerName[j] = bstream.ReadStringWithoutZeroes(20);

		bstream.Jump(2360);

		recordProfile.saveRecords = bstream.ReadString(4366);
	}
}
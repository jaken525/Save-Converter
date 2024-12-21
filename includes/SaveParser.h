#ifndef SAVEPARSER_H
#define SAVEPARSER_H

#include "Utils.h"

	const uint8_t sizeOfPlayerCars = 15;
	const uint8_t sizeOfModes = 5;
	const uint8_t sizeOfModeCars = 8;
	const uint8_t sizeOfBCModes = 7;

	struct Level
	{
		Time totalTime[10];
		Time lapTime[10];

		std::string playerName[10];
	};

	struct AllRecordLevels
	{
		Level levels[7];

		std::string saveRecords;
		std::string saveVersion = "";
	};

	struct PlayerCars
	{
		Car yourCars[sizeOfPlayerCars];
		Car quickRaceCars[sizeOfPlayerCars];
		Car marketCars[sizeOfPlayerCars];
		Car bonusCars[sizeOfPlayerCars];
		Car activatedCars[sizeOfPlayerCars];
	};

	struct OpponentCars
	{
		Car carModes[sizeOfModes];
	};

	struct ModeRaceSetting
	{
		uint32_t moneyForLevelPassing[sizeOfModes];
		uint32_t moneyForRecordPassing[sizeOfModes];

		uint8_t levelPassed[sizeOfModes];
		Map maps[sizeOfModes];

		 // BEFORE ALL CAR COLORS
		// AFTER ALL CAR IDS
		OpponentCars opponentCar[sizeOfModeCars];

		uint8_t laps[sizeOfModes];
		uint8_t countOfRacers[sizeOfModes]; // 0 ... 8
	};

	struct Profile
	{
		std::string profileName = "";

		std::string saveVersion = "";
		std::string saveName = "";
		std::string saveProfileName = "";
		std::string saveDate = "";

		float points = NULL;

		uint8_t passedTrials = NULL;
		uint8_t countOfOpenBonus = NULL; // 0 ... 4
		uint8_t timeAttackSeconds = NULL;
		uint8_t championshipLevels = NULL;

		float jumpDistances[sizeOfBCModes];

		uint32_t countOfSaves = NULL;
		uint32_t openFinalChallenge = NULL; // 0 ... 1
		
		ModeRaceSetting modes[sizeOfBCModes];
		// 0 ... 5 43 bytes NULL
		// 6 23 bytes NULL
		Map lastMap;

		uint8_t countOfCarsYouHaveInModes[sizeOfModes];
		uint8_t countOfCarsYouHaveInQuickRaceMode[sizeOfModes];
		uint8_t countOfCarsYouCanBuy[sizeOfModes];
		uint8_t countOfCarsYouHaveInBonus[sizeOfModes];
		const uint8_t unknown0[sizeOfModes] = { 1, 0, 1, 0, 1 };
		uint8_t currentCarInModes[sizeOfModes];
		uint8_t currentCarInBonus[sizeOfModes];
		uint8_t currentCarInMarket[sizeOfModes];

		PlayerCars cars[sizeOfModes];

		Profile() 
		{

		}

		~Profile()
		{

		}
	};

	class SaveParser
	{
	public:
		Profile localProfile;
		Profile localChampionshipProfile;
		AllRecordLevels recordProfile;

		SaveParser() {};
		~SaveParser()
		{
			bstream.Clear();
		};

		void LoadBCSaveFile(std::string filePath, std::string fileName);
		void LoadChampionshipSaveFile(std::string filePath, std::string fileName);
		void LoadRecordsSaveFile(std::string filePath, std::string fileName);
		bool LoadProfile(std::string path);

	private:
		std::string fileName;
		std::string filePath;

		BinaryStream bstream;
	};

#endif 
#ifndef MYUTILS_H
#define MYUTILS_H

#include <map>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "BinaryStream.h"

std::string OpenFilename();
std::string GetFilenamePath(const std::string str);
std::string GetFilenameFile(const std::string str);

struct Time
{
    int minutes;
    int seconds;
    int milliseconds;

    float distance;

    Time()
    {
        minutes = 0;
        seconds = 0;
        milliseconds = 0;

        distance = 0.0f;
    }
};

struct Map
{
    int id;
    int level;

    Map()
    {
        id = 0;
        level = 0;
    }

    Map(int id, int level)
    {
        this->id = id;
        this->level = level;
    }

    bool operator<(const Map& other) const
    {
        return std::tie(id, level) < std::tie(other.id, other.level);
    }
};

struct Car
{
    int id;
    int color;

    Car()
    {
        id = 0;
        color = 0;
    }

    Car(int id, int color)
    {
        this->id = id;
        this->color = color;
    }

    bool operator<(const Car& other) const 
    {
        return std::tie(id, color) < std::tie(other.id, other.color);
    }
};

enum RaceMode
{
    Speed = 0,
    Monster = 1,
    Cross = 2,
    Jump = 3,
    Buggy = 4,
    Derby = 5,

    Bonus = 6,
    WBC = 7,
};

extern std::string currentPath;

#endif
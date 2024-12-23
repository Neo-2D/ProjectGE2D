#pragma once
#include <string>
#include <fstream>
#include "Game.hpp"
#include "nlohmann/json.hpp"

class LevelLoader
{
public:
    LevelLoader();
    ~LevelLoader();

    static void loadLevel(const std::string& levelName);
};


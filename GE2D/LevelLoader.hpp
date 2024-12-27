#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "Game.hpp"
#include "nlohmann/json.hpp"

class LevelLoader
{
public:
    static LevelLoader& getInstance()
    {
        static LevelLoader instance;
        return instance;
    }

    void loadLevel(const std::string& levelName);
    void saveLevel();

    std::string getLoadedLevel() const { return loadedLevel; }

private:
    LevelLoader() = default;
    ~LevelLoader() = default;

    LevelLoader(const LevelLoader&) = delete;
    LevelLoader& operator=(const LevelLoader&) = delete;

    std::string loadedLevel;
};

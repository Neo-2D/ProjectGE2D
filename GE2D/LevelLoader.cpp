#include "LevelLoader.hpp"
using json = nlohmann::json;


/*JSON Level format
* {
*   "tiles": [
*       {
*           "type": "dirt",
*           "x": 0,
*           "y": 0
*       },
*       {
*           "type": "grass",
*           "x": 1,
*           "y": 0
*       }
*   ]
* }
*/

void LevelLoader::loadLevel(const std::string& levelName)
{
    std::cout << "Loading level: " << levelName << std::endl;
    //Count time to load level
    auto start = std::chrono::high_resolution_clock::now();

    Game::getInstance().clearSurfaceBuffer();

    std::ifstream file("assets/levels/" + levelName + ".json");
    json data = json::parse(file);
    loadedLevel = levelName;

    for (auto& tile : data["tiles"]) {
        std::string type = tile["type"];
        int x = tile["x"];
        int y = tile["y"];
        std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/textures/tiles/" + type + ".png", 1, 1, x, y, type);
        Game::getInstance().bufferizeSurface(std::move(s));
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Loaded level: " << levelName << " in " << duration.count() << " seconds" << std::endl;
}

void LevelLoader::saveLevel()
{
    std::string levelName = loadedLevel;
    json data;
    data["tiles"] = json::array();
    const auto& surfaces = Game::getInstance().getSurfaceBuffer();
    for (const auto& surface : surfaces) {
        json tile;
        tile["type"] = surface->getType();
        tile["x"] = surface->getX();
        tile["y"] = surface->getY();
        data["tiles"].push_back(tile);
    }
    std::ofstream file("assets/levels/" + levelName + ".json");
    file << data.dump(4);
    file.close();
    std::cout << "Saved level: " << levelName << std::endl;
}

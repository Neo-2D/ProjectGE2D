#include "LevelLoader.hpp"
using json = nlohmann::json;

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}



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
    Game::getInstance().clearSurfaceBuffer();

    std::ifstream file("assets/levels/" + levelName + ".json");
    json data = json::parse(file);

    for (auto& tile : data["tiles"]) {
        std::string type = tile["type"];
        int x = tile["x"];
        int y = tile["y"];
        std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/" + type + ".png", 1, 1, x, y);
        Game::getInstance().bufferizeSurface(std::move(s));
    }

    file.close();
}

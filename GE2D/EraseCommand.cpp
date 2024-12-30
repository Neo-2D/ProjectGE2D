#include "EraseCommand.hpp"

EraseCommand::EraseCommand(MapEditor& mapEditor, Vector2D position, const std::string& paintType) : 
    m_mapEditor(mapEditor), m_position(position), m_paintType(paintType)
{
}

void EraseCommand::execute()
{
    Game::getInstance().eraseSurface(m_position.x, m_position.y);
}

void EraseCommand::undo()
{
    std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/textures/tiles/" + m_paintType + ".png", 1, 1, m_position.x, m_position.y, m_paintType);
    Game::getInstance().bufferizeSurface(std::move(s));
}

bool EraseCommand::operator==(const Command& other) const
{
    const EraseCommand* otherCommand = dynamic_cast<const EraseCommand*>(&other);
    if (!otherCommand) {
        return false;
    }
    return m_position == otherCommand->m_position && m_paintType == otherCommand->m_paintType;
}

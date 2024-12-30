#pragma once
#include "Command.hpp"
#include "MapEditor.hpp"

class MapEditor;

class EraseCommand :
    public Command
{
private:
    MapEditor& m_mapEditor;
    Vector2D m_position;
    std::string m_paintType;

public:
    EraseCommand(MapEditor& mapEditor, Vector2D position, const std::string& paintType);
    void execute() override;
    void undo() override;
    bool operator==(const Command& other) const override;
};


#pragma once
#include <iostream>

class Command
{
public:
    Command() = default;
    ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual bool operator==(const Command& other) const = 0;
};


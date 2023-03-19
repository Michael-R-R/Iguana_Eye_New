#pragma once

#include <sol/sol.hpp>
#include <QVector2D>

class IEInput;

class LuaIEInput
{
    LuaIEInput();
    static LuaIEInput instance;

    // DOES NOT OWN THIS POINTER
    IEInput* input;

public:
    ~LuaIEInput();

    static void addToLua(IEInput* val, sol::table& gameTable);

private:
    bool isPressed(const char* key);
    QVector2D cursorPos();
    QVector2D wheelDelta();
};


#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>

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
    const glm::vec2& cursorPos() const;
};


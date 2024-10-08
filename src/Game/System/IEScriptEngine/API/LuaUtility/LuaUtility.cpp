#include "LuaUtility.h"
#include "IEHash.h"

LuaUtility LuaUtility::instance;

LuaUtility::LuaUtility()
{

}

LuaUtility::~LuaUtility()
{

}

void LuaUtility::addToLua(sol::table& utilityTable)
{
    utilityTable["IEHash"] = instance;
    utilityTable.new_usertype<LuaUtility>("", sol::no_constructor,
                                          "compute", &LuaUtility::computeHash);
}

uint64_t LuaUtility::computeHash(const char* str)
{
    // TODO this throws an exception in lua (integer value will be misrepresented in lua)
    return IEHash::Compute(str);
}

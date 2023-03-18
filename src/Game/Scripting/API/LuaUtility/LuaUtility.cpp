#include "LuaUtility.h"
#include "IEHash.h"

LuaUtility::LuaUtility(sol::table& utilityTable)
{
    utilityTable["hashing"] = this;
    utilityTable.new_usertype<LuaUtility>("", sol::no_constructor,
                                          "compute", &LuaUtility::computeHash);
}

LuaUtility::~LuaUtility()
{

}

unsigned long long LuaUtility::computeHash(const char* str)
{
    return IEHash::Compute(str);
}

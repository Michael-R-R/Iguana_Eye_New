#include "LuaIEECSTransformSystem.h"
#include "IEECSTransformSystem.h"

LuaIEECSTransformSystem::LuaIEECSTransformSystem(sol::state& lua)
{
    lua.new_usertype<IEECSTransformSystem>("", sol::no_constructor,
                                           "lookUpIndex", &IEECSTransformSystem::lookUpIndex,
                                           "getPosition", &IEECSTransformSystem::getPosition,
                                           "getRotation", &IEECSTransformSystem::getRotation,
                                           "getScale", &IEECSTransformSystem::getScale,
                                           "setPosition", &IEECSTransformSystem::setPosition,
                                           "setRotation", &IEECSTransformSystem::setRotation,
                                           "setScale", &IEECSTransformSystem::setScale);
}

LuaIEECSTransformSystem::~LuaIEECSTransformSystem()
{

}

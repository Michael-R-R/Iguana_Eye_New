#include "LuaIEECSTransformSystem.h"
#include "IEECSTransformSystem.h"

void LuaIEECSTransformSystem::addToLua(sol::state& lua)
{
    lua.new_usertype<IEECSTransformSystem>("", sol::no_constructor,
                                           "lookUpIndex", &IEECSTransformSystem::lookUpIndex,
                                           "getPosition", &IEECSTransformSystem::getPosition,
                                           "getRotation", &IEECSTransformSystem::getRotation,
                                           "getScale", &IEECSTransformSystem::getScale,
                                           "setPosition", &IEECSTransformSystem::setPosition,
                                           "setRotation", sol::overload(sol::resolve<const int, const QVector3D&>(&IEECSTransformSystem::setRotation),
                                                                        sol::resolve<const int, const QVector4D&>(&IEECSTransformSystem::setRotation)),
                                           "setScale", &IEECSTransformSystem::setScale);
}

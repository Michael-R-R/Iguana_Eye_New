#include "LuaIEECSTransformSystem.h"
#include "IEECSTransformSystem.h"
#include <glm/glm.hpp>

void LuaIEECSTransformSystem::addToLua(sol::state& lua)
{
    lua.new_usertype<IEECSTransformSystem>("", sol::no_constructor,
                                           "lookUpIndex", &IEECSTransformSystem::lookUpIndex,
                                           "getPosition", &IEECSTransformSystem::getPosition,
                                           "getRotation", &IEECSTransformSystem::getRotation,
                                           "getScale", &IEECSTransformSystem::getScale,
                                           "setPosition", &IEECSTransformSystem::setPosition,
                                           "setRotation", sol::overload(sol::resolve<const int, const glm::vec3&>(&IEECSTransformSystem::setRotation),
                                                                        sol::resolve<const int, const glm::vec4&>(&IEECSTransformSystem::setRotation)),
                                           "setScale", &IEECSTransformSystem::setScale);
}

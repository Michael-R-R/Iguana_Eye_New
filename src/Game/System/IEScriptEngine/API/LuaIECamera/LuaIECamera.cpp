#include "LuaIECamera.h"
#include "IECamera.h"
#include <glm/glm.hpp>

void LuaIECamera::addToLua(sol::state& lua)
{
    lua.new_usertype<IECamera>("", sol::no_constructor,
                               "projection", sol::property(&IECamera::getProjection, &IECamera::setProjection),
                               "view", sol::property(&IECamera::getView),
                               "up", sol::property(&IECamera::getUp),
                               "near", sol::property(&IECamera::getNearPlane, &IECamera::setNearPlane),
                               "far", sol::property(&IECamera::getFarPlane, &IECamera::setFarPlane),
                               "fov", sol::property(&IECamera::getFOV, &IECamera::setFOV),
                               "speed", sol::property(&IECamera::getSpeed, &IECamera::setSpeed),
                               "sensitivity", sol::property(&IECamera::getSensitivity, &IECamera::setSensitivity),
                               "updateView", sol::overload(sol::resolve<const glm::vec3&, const glm::vec3&>(&IECamera::updateView),
                                                           sol::resolve<const glm::vec3&, const glm::vec4&>(&IECamera::updateView)));
}

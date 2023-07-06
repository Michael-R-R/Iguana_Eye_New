#include "LuaIECamera.h"
#include "IECamera.h"

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
                               "updateView", &IECamera::updateView);
}

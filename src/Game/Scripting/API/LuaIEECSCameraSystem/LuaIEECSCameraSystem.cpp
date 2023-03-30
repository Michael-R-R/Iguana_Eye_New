#include "LuaIEECSCameraSystem.h"
#include "IEECSCameraSystem.h"
#include "LuaIECamera.h"
#include "IECamera.h"

void LuaIEECSCameraSystem::addToLua(sol::state& lua)
{
    LuaIECamera::addToLua(lua);

    lua.new_usertype<IEECSCameraSystem>("", sol::no_constructor,
                                        "lookUpIndex", &IEECSCameraSystem::lookUpIndex,
                                        "getActiveIndex", &IEECSCameraSystem::getActiveIndex,
                                        "setActiveIndex", &IEECSCameraSystem::setActiveIndex,
                                        "getActiveCamera", &IEECSCameraSystem::getActiveCamera,
                                        "getAttachedCamera", &IEECSCameraSystem::getAttachedCamera,
                                        "getCameraId", &IEECSCameraSystem::getCameraId,
                                        "setCameraId", &IEECSCameraSystem::setCameraId);
}

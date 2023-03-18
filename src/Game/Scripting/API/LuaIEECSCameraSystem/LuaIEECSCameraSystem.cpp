#include "LuaIEECSCameraSystem.h"
#include "IEECSCameraSystem.h"
#include "LuaIECamera.h"
#include "IECamera.h"

LuaIEECSCameraSystem::LuaIEECSCameraSystem(sol::state& lua) :
    luaCamera(std::make_unique<LuaIECamera>(lua))
{
    lua.new_usertype<IEECSCameraSystem>("", sol::no_constructor,
                                        "lookUpIndex", &IEECSCameraSystem::lookUpIndex,
                                        "getActiveIndex", &IEECSCameraSystem::getActiveIndex,
                                        "setActiveIndex", &IEECSCameraSystem::setActiveIndex,
                                        "getHasDirtyProj", &IEECSCameraSystem::getHasDirtyProj,
                                        "setHasDirtyProj", &IEECSCameraSystem::setHasDirtyProj,
                                        "getActiveCamera", &IEECSCameraSystem::getActiveCamera,
                                        "getAttachedCamera", &IEECSCameraSystem::getAttachedCamera,
                                        "getCameraId", &IEECSCameraSystem::getCameraId,
                                        "setCameraId", &IEECSCameraSystem::setCameraId);
}

LuaIEECSCameraSystem::~LuaIEECSCameraSystem()
{

}

#include "LuaGlobalEnum.h"
#include "IEComponentType.h"

LuaGlobalEnum::LuaGlobalEnum(sol::table& enumTable)
{
    enumTable.new_enum("component",
                       "Name", IEComponentType::Name,
                       "Hierarchy", IEComponentType::Hierarchy,
                       "Input", IEComponentType::Input,
                       "Script", IEComponentType::Script,
                       "Physics", IEComponentType::Physics,
                       "Transform", IEComponentType::Transform,
                       "Camera", IEComponentType::Camera,
                       "Mesh", IEComponentType::Mesh,
                       "Material", IEComponentType::Material,
                       "Shader", IEComponentType::Shader,
                       "Renderable", IEComponentType::Renderable);

}

LuaGlobalEnum::~LuaGlobalEnum()
{

}

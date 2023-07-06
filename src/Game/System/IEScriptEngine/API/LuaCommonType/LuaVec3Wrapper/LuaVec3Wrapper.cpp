#include "LuaVec3Wrapper.h"

LuaVec3Wrapper::LuaVec3Wrapper() :
    vec3()
{

}

LuaVec3Wrapper::LuaVec3Wrapper(float n1, float n2, float n3) :
    vec3(n1, n2, n3)
{

}

LuaVec3Wrapper::LuaVec3Wrapper(const QVector3D& n) :
    vec3(n)
{

}

LuaVec3Wrapper::LuaVec3Wrapper(const QVector4D& n) :
    vec3(n.toVector3D())
{

}

LuaVec3Wrapper::LuaVec3Wrapper(const LuaVec3Wrapper& n) :
    vec3(n.vec3)
{

}

LuaVec3Wrapper::~LuaVec3Wrapper()
{

}

void LuaVec3Wrapper::addToLua(sol::state& lua)
{
    lua.new_usertype<LuaVec3Wrapper>("IEVec3", sol::constructors<LuaVec3Wrapper(),
                                     LuaVec3Wrapper(float, float, float),
                                     LuaVec3Wrapper(const QVector3D&),
                                     LuaVec3Wrapper(const QVector4D&),
                                     LuaVec3Wrapper(const LuaVec3Wrapper&)>(),
                                     "x", &LuaVec3Wrapper::x,
                                     "y", &LuaVec3Wrapper::y,
                                     "z", &LuaVec3Wrapper::z,
                                     "normalize", &LuaVec3Wrapper::normalize,
                                     "cross", &LuaVec3Wrapper::cross,
                                     "get", &LuaVec3Wrapper::get,
                                     sol::meta_function::addition, &LuaVec3Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaVec3Wrapper::operator -,
                                     sol::meta_function::multiplication, sol::overload(sol::resolve<const LuaVec3Wrapper&>(&LuaVec3Wrapper::operator *),
                                                                                       sol::resolve<float>(&LuaVec3Wrapper::operator *)),
                                     sol::meta_function::division, &LuaVec3Wrapper::operator /);
}

LuaVec3Wrapper LuaVec3Wrapper::normalize()
{
    vec3.normalize();
    return LuaVec3Wrapper(vec3);
}

LuaVec3Wrapper LuaVec3Wrapper::cross(LuaVec3Wrapper v1, LuaVec3Wrapper v2)
{
    vec3 = QVector3D::crossProduct(v1.vec3, v2.vec3);
    return LuaVec3Wrapper(vec3);
}

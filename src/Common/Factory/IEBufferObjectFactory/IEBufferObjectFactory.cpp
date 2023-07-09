#include "IEBufferObjectFactory.h"
#include "IEIndexBufferObject.h"
#include "IEVertexBufferObject.h"
#include <QObject>
#include <glm/glm.hpp>

IEBufferObject* IEBufferObjectFactory::make(const IEBufferType type, QObject* parent)
{
    switch(type)
    {
    case IEBufferType::Index: { return new IEIndexBufferObject(parent); }
    case IEBufferType::Vec2: { return new IEVertexBufferObject<glm::vec2>(type, parent); }
    case IEBufferType::Vec3: { return new IEVertexBufferObject<glm::vec3>(type, parent); }
    case IEBufferType::Vec4: { return new IEVertexBufferObject<glm::vec4>(type, parent); }
    case IEBufferType::Mat4: { return new IEVertexBufferObject<glm::mat4>(type, parent); }
    default: { return nullptr; }
    }
}

IEBufferObject* IEBufferObjectFactory::make(const IEBufferType type,
                                            const int stride,
                                            const int offset,
                                            const int divisor,
                                            QObject* parent)
{
    switch(type)
    {
    case IEBufferType::Vec2: { return new IEVertexBufferObject<glm::vec2>(type, 2, stride, offset, divisor, parent); }
    case IEBufferType::Vec3: { return new IEVertexBufferObject<glm::vec3>(type, 3, stride, offset, divisor, parent); }
    case IEBufferType::Vec4: { return new IEVertexBufferObject<glm::vec4>(type, 4, stride, offset, divisor, parent); }
    case IEBufferType::Mat4: { return new IEVertexBufferObject<glm::mat4>(type, 4, stride, offset, divisor, parent); }
    default: { return nullptr; }
    }
}

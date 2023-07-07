#include "IEBufferObjectFactory.h"
#include "IEIndexBufferObject.h"
#include "IEVertexBufferObject.h"
#include <QObject>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

IEBufferObject* IEBufferObjectFactory::make(const IEBufferType type, QObject* parent)
{
    switch(type)
    {
    case IEBufferType::Index: { return new IEIndexBufferObject(parent); }
    case IEBufferType::Vec2: { return new IEVertexBufferObject<QVector2D>(type, parent); }
    case IEBufferType::Vec3: { return new IEVertexBufferObject<QVector3D>(type, parent); }
    case IEBufferType::Vec4: { return new IEVertexBufferObject<QVector4D>(type, parent); }
    case IEBufferType::Mat4: { return new IEVertexBufferObject<QMatrix4x4>(type, parent); }
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
    case IEBufferType::Vec2: { return new IEVertexBufferObject<QVector2D>(type, 2, stride, offset, divisor, parent); }
    case IEBufferType::Vec3: { return new IEVertexBufferObject<QVector3D>(type, 3, stride, offset, divisor, parent); }
    case IEBufferType::Vec4: { return new IEVertexBufferObject<QVector4D>(type, 4, stride, offset, divisor, parent); }
    case IEBufferType::Mat4: { return new IEVertexBufferObject<QMatrix4x4>(type, 4, stride, offset, divisor, parent); }
    default: { return nullptr; }
    }
}

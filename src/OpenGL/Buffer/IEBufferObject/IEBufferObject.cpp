#include "IEBufferObject.h"

IEBufferObject::IEBufferObject(QOpenGLBuffer::Type type, QObject* parent) :
    QOpenGLBuffer(type), IEObject(parent),
    bufferType(IEBufferType::Unknown),
    usage(QOpenGLBuffer::StaticDraw)
{
    this->setUsagePattern(usage);
}

IEBufferObject::~IEBufferObject()
{
    if(this->isCreated())
        this->destroy();
}

QDataStream& IEBufferObject::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& buffer = static_cast<const IEBufferObject&>(obj);

    out << buffer.bufferType << buffer.usage;

    return out;
}

QDataStream& IEBufferObject::deserialize(QDataStream& in, Serializable& obj)
{
    auto& buffer = static_cast<IEBufferObject&>(obj);

    in >> buffer.bufferType >> buffer.usage;

    return in;
}

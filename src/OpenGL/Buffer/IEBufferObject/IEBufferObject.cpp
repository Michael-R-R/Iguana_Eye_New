#include "IEBufferObject.h"

IEBufferObject::IEBufferObject(QOpenGLBuffer::Type glType, IEBufferType ieType,
                               bool instanced, QObject* parent) :
    QOpenGLBuffer(glType), IEObject(parent),
    bufferType(ieType),
    usage(QOpenGLBuffer::StaticDraw),
    isInstanced(instanced)
{
    this->setUsagePattern(usage);
}

IEBufferObject::~IEBufferObject()
{
    if(this->isCreated())
        this->destroy();
}

QDataStream& IEBufferObject::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& buffer = static_cast<const IEBufferObject&>(obj);

    out << buffer.bufferType << buffer.usage << buffer.isInstanced;

    return out;
}

QDataStream& IEBufferObject::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& buffer = static_cast<IEBufferObject&>(obj);

    in >> buffer.bufferType >> buffer.usage >> buffer.isInstanced;

    return in;
}

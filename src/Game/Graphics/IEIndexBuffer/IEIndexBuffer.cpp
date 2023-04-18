#include "IEIndexBuffer.h"

IEIndexBuffer::IEIndexBuffer(QObject* parent) :
    IEBuffer(QOpenGLBuffer::IndexBuffer, parent)
{

}

IEIndexBuffer::IEIndexBuffer(const QVector<unsigned>& data_, QObject* parent) :
    IEBuffer(QOpenGLBuffer::IndexBuffer, data_, parent)
{

}

IEIndexBuffer::~IEIndexBuffer()
{

}

void IEIndexBuffer::build(const int)
{
    if(!this->isCreated())
        this->create();

    this->setUsagePattern(QOpenGLBuffer::StaticDraw);
    this->bind();
    this->allocate(bufferData.constData(), (int)(bufferData.size() * sizeof(unsigned)));
}

QDataStream& IEIndexBuffer::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& buffer = static_cast<const IEIndexBuffer&>(obj);

    out << buffer.bufferData;

    return out;
}

QDataStream& IEIndexBuffer::deserialize(QDataStream& in, Serializable& obj)
{
    auto& buffer = static_cast<IEIndexBuffer&>(obj);

    in >> buffer.bufferData;

    return in;
}

#include "IEIndexBuffer.h"

IEIndexBuffer::IEIndexBuffer() :
    IEBuffer(QOpenGLBuffer::IndexBuffer)
{

}

IEIndexBuffer::IEIndexBuffer(const QVector<unsigned>& data_) :
    IEBuffer(QOpenGLBuffer::IndexBuffer, data_)
{

}

IEIndexBuffer::IEIndexBuffer(const IEIndexBuffer& other) :
    IEBuffer(QOpenGLBuffer::IndexBuffer, other.bufferData)
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

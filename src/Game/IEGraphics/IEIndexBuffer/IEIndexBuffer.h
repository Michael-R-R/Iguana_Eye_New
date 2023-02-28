#pragma once

#include <QDataStream>

#include "IEBuffer.h"

class IEIndexBuffer : public IEBuffer<unsigned>
{

public:
    IEIndexBuffer() :
        IEBuffer(QOpenGLBuffer::IndexBuffer)
    {

    }

    IEIndexBuffer(const QVector<unsigned>& data_) :
        IEBuffer(QOpenGLBuffer::IndexBuffer, data_)
    {

    }

    IEIndexBuffer(const IEIndexBuffer& other) :
        IEBuffer(QOpenGLBuffer::IndexBuffer, other.bufferData)
    {

    }

    ~IEIndexBuffer() {}

    void build(const int = -1) override
    {
        if(!this->isCreated())
            this->create();

        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->bind();
        this->allocate(bufferData.data(), (int)(bufferData.size() * sizeof(unsigned)));
    }

    friend QDataStream& operator<<(QDataStream& out, const IEIndexBuffer& buffer)
    {
        out << buffer.bufferData;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEIndexBuffer& buffer)
    {
        in >> buffer.bufferData;

        return in;
    }
};


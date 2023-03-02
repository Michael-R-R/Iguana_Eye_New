#pragma once

#include <QDataStream>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>

#include "IEBuffer.h"

template <class T>
class IEVertexBuffer : public IEBuffer<T>
{
    int tuple;
    int stride;
    int divisor;
    int dataSize;
    bool isInstanced;

public:
    IEVertexBuffer() :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer),
        tuple(0), stride(0), divisor(0), dataSize(0),
        isInstanced(false)
    {

    }

    IEVertexBuffer(const QVector<T>& data_, const int dataSize_, const int tuple_,
                   const int stride_ = 0, const int divisor_ = 0) :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer, data_),
        tuple(tuple_), stride(stride_),
        divisor(divisor_), dataSize(dataSize_),
        isInstanced((divisor > 0))
    {

    }

    IEVertexBuffer(const IEVertexBuffer& other) :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer, other.bufferData),
        tuple(other.tuple), stride(other.stride),
        divisor(other.divisor), dataSize(other.dataSize),
        isInstanced(other.isInstanced)
    {

    }

    ~IEVertexBuffer() {}

    void build(const int attribLoc = -1) override
    {
        if(!this->isCreated())
            this->create();

        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->bind();
        this->allocate(this->bufferData.data(), (int)(this->bufferData.size() * dataSize));

        if(attribLoc < 0)
            return;

        QOpenGLFunctions* func = QOpenGLContext::currentContext()->functions();
        if(divisor < 1)
        {
            func->glVertexAttribPointer(attribLoc, tuple, GL_FLOAT, false, stride, 0);
            func->glEnableVertexAttribArray(attribLoc);
        }
        else
        {
            QOpenGLExtraFunctions* extraFunc = QOpenGLContext::currentContext()->extraFunctions();
            for(int i = 0; i < divisor; i++)
            {
                func->glVertexAttribPointer(attribLoc + i, tuple, GL_FLOAT, false, stride, (void*)(i * (dataSize / 4)));
                func->glEnableVertexAttribArray(attribLoc + i);
                extraFunc->glVertexBindingDivisor(attribLoc + i, 1);
            }
        }
    }

    void reallocate()
    {
        if(!this->isCreated())
            return;

        this->bind();
        this->allocate(this->bufferData.data(), (int)(this->bufferData.size() * dataSize));
        this->release();
    }

    void subAllocate(const int offset, const void* subData)
    {
        if(!this->indexBoundsCheck(offset))
            return;

        if(!this->isCreated())
            return;

        this->bind();
        this->write((offset * dataSize), subData, dataSize);
        this->release();
    }

    bool getIsInstanced() const { return isInstanced; }

    friend QDataStream& operator<<(QDataStream& out, const IEVertexBuffer<T>& buffer)
    {
        out << buffer.bufferData
            << buffer.tuple
            << buffer.stride
            << buffer.divisor
            << buffer.dataSize
            << buffer.isInstanced;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEVertexBuffer<T>& buffer)
    {
        in >> buffer.bufferData
           >> buffer.tuple
           >> buffer.stride
           >> buffer.divisor
           >> buffer.dataSize
           >> buffer.isInstanced;

        return in;
    }
};


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

public:
    IEVertexBuffer() :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer),
        tuple(0), stride(0), divisor(0)
    {

    }

    IEVertexBuffer(const QVector<T>& data_, const int tuple_,
                   const int stride_ = 0, const int divisor_ = 0) :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer, data_),
        tuple(tuple_), stride(stride_), divisor(divisor_)
    {

    }

    IEVertexBuffer(const IEVertexBuffer& other) :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer, other.bufferData),
        tuple(other.tuple), stride(other.stride), divisor(other.divisor)
    {

    }

    ~IEVertexBuffer() {}

    void build(const int attribLoc = -1) override
    {
        if(!this->isCreated())
            this->create();
        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->bind();
        this->allocate(this->bufferData.data(), (int)(this->bufferData.size() * sizeof(T)));

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
                func->glVertexAttribPointer(attribLoc + i, tuple, GL_FLOAT, false, stride, (void*)(i * sizeof(T)));
                func->glEnableVertexAttribArray(attribLoc + i);
                extraFunc->glVertexBindingDivisor(attribLoc + i, 1);
            }
        }
    }

    friend QDataStream& operator<<(QDataStream& out, const IEVertexBuffer<T>& buffer)
    {
        out << buffer.bufferData
            << buffer.tuple
            << buffer.stride
            << buffer.divisor;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEVertexBuffer<T>& buffer)
    {
        in >> buffer.bufferData
           >> buffer.tuple
           >> buffer.stride
           >> buffer.divisor;

        return in;
    }
};


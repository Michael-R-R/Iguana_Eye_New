#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>

#include "IEBuffer.h"
#include "Serializable.h"

template <class T>
class IEVertexBuffer : public IEBuffer<T>, public Serializable
{
    int typeSize;
    int tuple;
    int stride;
    int divisor;
    int ptrSize;
    bool isInstanced;

public:
    IEVertexBuffer() :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer),
        typeSize(0), tuple(0), stride(0),
        divisor(0), ptrSize(0),
        isInstanced(false)
    {

    }

    IEVertexBuffer(const QVector<T>& data_, const int typeSize_, const int tuple_,
                   const int stride_, const int divisor_, const int ptrSize_) :
        IEBuffer<T>(QOpenGLBuffer::VertexBuffer, data_),
        typeSize(typeSize_), tuple(tuple_), stride(stride_),
        divisor(divisor_), ptrSize(ptrSize_),
        isInstanced((divisor > 0))
    {

    }

    IEVertexBuffer(const IEVertexBuffer&) = delete;

    ~IEVertexBuffer() {}

    void build(const int attribLoc) override
    {
        if(attribLoc < 0)
            return;

        if(!this->isCreated())
            this->create();

        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->bind();
        this->allocate(this->bufferData.constData(), (int)(this->bufferData.size() * typeSize));

        QOpenGLFunctions* func = QOpenGLContext::currentContext()->functions();
        if(divisor < 1)
        {
            func->glVertexAttribPointer(attribLoc, tuple, GL_FLOAT, GL_FALSE, stride, (void*)(size_t)ptrSize);
            func->glEnableVertexAttribArray(attribLoc);
        }
        else
        {
            QOpenGLExtraFunctions* extraFunc = QOpenGLContext::currentContext()->extraFunctions();
            for(int i = 0; i < divisor; i++)
            {
                func->glVertexAttribPointer(attribLoc + i, tuple, GL_FLOAT, GL_FALSE, stride, (void*)(size_t)(i * ptrSize));
                func->glEnableVertexAttribArray(attribLoc + i);
                extraFunc->glVertexAttribDivisor(attribLoc + i, 1);
            }
        }
    }

    void reallocate()
    {
        if(!this->isCreated())
            return;

        this->bind();
        this->allocate(this->bufferData.constData(), (int)(this->bufferData.size() * typeSize));
        this->release();
    }

    void subAllocate(const int offset)
    {
        if(!this->indexBoundsCheck(offset))
            return;

        if(!this->isCreated())
            return;

        this->bind();
        this->write((offset * typeSize), &this->bufferData[offset], typeSize);
        this->release();
    }

    bool getIsInstanced() const
    {
        return isInstanced;
    }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override
    {
        const auto& buffer = static_cast<const IEVertexBuffer&>(obj);

        out << buffer.bufferData << buffer.typeSize
            << buffer.tuple << buffer.stride
            << buffer.divisor << buffer.ptrSize
            << buffer.isInstanced;

        return out;
    }

    QDataStream& deserialize(QDataStream &in, Serializable &obj) override
    {
        auto& buffer = static_cast<IEVertexBuffer&>(obj);

        in >> buffer.bufferData >> buffer.typeSize
           >> buffer.tuple >> buffer.stride
           >> buffer.divisor >> buffer.ptrSize
           >> buffer.isInstanced;

        return in;
    }
};


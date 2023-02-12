#pragma once

#include <QDataStream>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>

template <class T>
class IEBuffer : public QOpenGLBuffer
{
   QVector<T> data;
   int tuple;
   int stride;
   int divisor;

public:
    IEBuffer(QOpenGLBuffer::Type type) :
        QOpenGLBuffer(type),
        data(), tuple(0),
        stride(0), divisor(0)
    {

    }

    IEBuffer(const IEBuffer& other) :
        QOpenGLBuffer(other.type()),
        data(other.data), tuple(other.tuple),
        stride(other.stride), divisor(other.divisor)
    {

    }

    ~IEBuffer()
    {
        if(this->isCreated())
            this->destroy();
    }

    void initData(const QVector<T>& data_, const int stride_ = 0, const int divisor_ = 0)
    {
        data = data_;
        tuple = (sizeof(T) / 4);
        stride = stride_;
        divisor = divisor_;
    }

    void initData(const QVector<T>& data_, const int tuple_, const int stride_ = 0, const int divisor_ = 0)
    {
        data = data_;
        tuple = tuple_;
        stride = stride_;
        divisor = divisor_;
    }

    void build(const int attribLoc)
    {
        if(!this->isCreated())
            this->create();
        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->bind();
        this->allocate(data.data(), (int)(data.size() * sizeof(T)));

        if(this->type() == QOpenGLBuffer::VertexBuffer)
        {
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
    }

    void subAllocate(const int offset, const void* subData)
    {
        if(!this->isCreated())
            return;

        this->bind();
        this->write((int)(offset * sizeof(T)), subData, sizeof(T));
        this->release();
    }

    friend QDataStream& operator<<(QDataStream& out, const IEBuffer<T>& buffer)
    {
        out << buffer.data
            << buffer.tuple
            << buffer.stride
            << buffer.divisor;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEBuffer<T>& buffer)
    {
        in >> buffer.data
            >> buffer.tuple
            >> buffer.stride
            >> buffer.divisor;

        return in;
    }
};

#pragma once

#include <QOpenGLBuffer>
#include <QVector>

template <class T>
class IEBuffer : public QOpenGLBuffer
{
protected:
   QVector<T> bufferData;

public:
   IEBuffer(QOpenGLBuffer::Type type) :
       QOpenGLBuffer(type),
       bufferData()
   {

   }

    IEBuffer(QOpenGLBuffer::Type type, const QVector<T>& data_) :
        QOpenGLBuffer(type),
        bufferData(data_)
    {

    }

    IEBuffer(const IEBuffer& other) :
        QOpenGLBuffer(other.type()),
        bufferData(other.bufferData)
    {

    }

    ~IEBuffer()
    {
        if(this->isCreated())
            this->destroy();
    }

    virtual void build(const int attribLoc = -1) = 0;

    void subAllocate(const int offset, const void* subData)
    {
        if(!this->isCreated())
            return;

        this->bind();
        this->write((int)(offset * sizeof(T)), subData, sizeof(T));
        this->release();
    }
};

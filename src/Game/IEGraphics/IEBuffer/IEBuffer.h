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

    int appendBufferValue(const T& val)
    {
        int index = bufferData.size();

        bufferData.append(val);

        return index;
    }

    bool removeBufferValue(const int indexToRemove)
    {
        if(indexToRemove < 0 || indexToRemove > bufferData.size())
            return false;

        const int lastIndex = bufferData.size() - 1;

        bufferData[indexToRemove] = bufferData[lastIndex];

        bufferData.removeLast();

        return true;
    }

    void setBufferValue(const int index, const T& val)
    {
        if(index < 0 || index > bufferData.size())
            return;

        bufferData[index] = val;
    }
};

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
        if(bufferData.size() == 0)
            return false;

        if(!indexBoundsCheck(indexToRemove))
            return false;

        const int lastIndex = bufferData.size() - 1;

        bufferData[indexToRemove] = bufferData[lastIndex];

        bufferData.removeLast();

        return true;
    }

    bool indexBoundsCheck(const int index) const
    {
        return (index > -1 && index < bufferData.size());
    }

    const QVector<T>& getBufferData() const
    {
        return bufferData;
    }

    T getBufferValue(const int index) const
    {
        if(!indexBoundsCheck(index))
            return T();

        return bufferData[index];
    }

    void setBufferData(const QVector<T>& data)
    {
        bufferData.clear();
        bufferData = data;
    }

    void setBufferValue(const int index, const T& val)
    {
        if(!indexBoundsCheck(index))
            return;

        bufferData[index] = val;
    }
};

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

    void initData(const QVector<T>& data_, const int tuple_,
                  const int stride_, const int divisor_)
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

    const QVector<T>& getData() const { return data; }
    int getTuple() const { return tuple; }
    int getStride() const { return stride; }
    int getDivisor() const { return divisor; }

    void setData(const QVector<T>& val) { data = val; }
    void setTuple(const int val) { tuple = val; }
    void setStride(const int val) { stride = val; }
    void setDivisor(const int val) { divisor = val; }
};

template <class T>
QDataStream& operator<<(QDataStream& out, const IEBuffer<T>& buffer)
{
    out << buffer.getData()
        << buffer.getTuple()
        << buffer.getStride()
        << buffer.getDivisor();

    return out;
}

template <class T>
QDataStream& operator>>(QDataStream& in, IEBuffer<T>& buffer)
{
    QVector<T> data;
    int tuple;
    int stride;
    int divisor;

    in >> data
       >> tuple
       >> stride
       >> divisor;

    buffer.setData(data);
    buffer.setTuple(tuple);
    buffer.setStride(stride);
    buffer.setDivisor(divisor);

    return in;
}

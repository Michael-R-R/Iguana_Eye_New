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
   unsigned tuple;
   unsigned stride;
   unsigned divisor;

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

    ~IEBuffer() {}

    void build(QVector<T>& data_, const unsigned tuple_,
               const unsigned stride_, const unsigned divisor_,
               const int attribLoc)
    {
        data = data_;
        tuple = tuple_;
        stride = stride_;
        divisor = divisor_;

        this->setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->create();
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
                for(unsigned i = 0; i < divisor; i++)
                {
                    func->glVertexAttribPointer(attribLoc + i, tuple, GL_FLOAT, false, stride, (void*)(i * sizeof(T)));
                    func->glEnableVertexAttribArray(attribLoc + i);
                    extraFunc->glVertexBindingDivisor(attribLoc + i, 1);
                }
            }
        }
    }

    void rebuild(const int attribLoc)
    {
        this->build(data, tuple, stride, divisor, attribLoc);
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
    unsigned getTuple() const { return tuple; }
    unsigned getStride() const { return stride; }
    unsigned getDivisor() const { return divisor; }

    void setData(const QVector<T>& val) { data = val; }
    void setTuple(const unsigned val) { tuple = val; }
    void setStride(const unsigned val) { stride = val; }
    void setDivisor(const unsigned val) { divisor = val; }
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
    unsigned tuple;
    unsigned stride;
    unsigned divisor;

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

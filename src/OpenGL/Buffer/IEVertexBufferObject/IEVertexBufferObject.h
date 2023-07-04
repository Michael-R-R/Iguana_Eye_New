#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>

#include "IEBufferObject.h"

template<class T>
class IEVertexBufferObject : public IEBufferObject
{
protected:
    QVector<T> values;
    int tuple;
    int stride;
    int offset;
    int divisor;

public:
    IEVertexBufferObject(const IEBufferType ieType, QObject* parent = nullptr) :
        IEBufferObject(QOpenGLBuffer::VertexBuffer, ieType, false, parent),
        values(), tuple(0), stride(0), offset(0), divisor(0)
    {

    }

    IEVertexBufferObject(const IEBufferType ieType,
                         const int t, const int s,
                         const int o, const int d,
                         QObject* parent = nullptr) :
        IEBufferObject(QOpenGLBuffer::VertexBuffer, ieType, (d > 0), parent),
        values(), tuple(t), stride(s), offset(o), divisor(d)
    {

    }

    IEVertexBufferObject(const IEBufferType ieType,
                         const QVector<T>& vals,
                         const int t, const int s,
                         const int o, const int d,
                         QObject* parent = nullptr) :
        IEBufferObject(QOpenGLBuffer::VertexBuffer, ieType, (d > 0), parent),
        values(vals), tuple(t), stride(s), offset(o), divisor(d)
    {

    }

    virtual ~IEVertexBufferObject()
    {

    }

    IEVertexBufferObject(const IEVertexBufferObject&) = delete;

    int appendValue(const std::any& val) override
    {
        const int index = values.size();

        if(val.has_value())
            values.append(std::any_cast<T>(val));
        else
            values.append(T{});

        return index;
    }

    bool removeValue(const int index) override
    {
        if(index < 0 || index >= values.size())
            return false;

        const int lastIndex = values.size() - 1;
        values[index] = values[lastIndex];
        values.removeLast();

        return true;
    }

    void handleAllocate(const bool doRelease = false) override
    {
        this->bind();

        this->allocate(values.constData(), (int)(values.size() * sizeof(T)));

        if(doRelease)
            this->release();
    }

    void handleSuballocate(const int index) override
    {
        if(index < 0 || index > values.size() - 1)
            return;

        if(!isCreated())
            return;

        int typeSize = sizeof(T);

        this->bind();
        this->write((index * typeSize), &values[index], typeSize);
        this->release();
    }

    void build(const int loc = -1) override
    {
        if(this->isCreated())
            this->destroy();

        this->create();
        this->handleAllocate();

        auto* gl = QOpenGLContext::currentContext()->functions();
        if(!isInstanced)
        {
            gl->glVertexAttribPointer(loc, tuple, GL_FLOAT, GL_FALSE, stride, (void*)(size_t)offset);
            gl->glEnableVertexAttribArray(loc);
        }
        else
        {
            auto* glExtra = QOpenGLContext::currentContext()->extraFunctions();
            for(int i = 0; i < divisor; i++)
            {
                gl->glVertexAttribPointer(loc + i, tuple, GL_FLOAT, GL_FALSE, stride, (void*)(size_t)(i * offset));
                gl->glEnableVertexAttribArray(loc + i);
                glExtra->glVertexBindingDivisor(loc + i, 1);
            }
        }
    }

    int size() const override
    {
        return values.size();
    }

    std::any getValue(const int index) override
    {
        if(index < 0 || index >= values.size())
            return std::any{};

        return values[index];
    }

    std::any getValues() const override
    {
        return values;
    }

    void setValue(const int index, const std::any& val)
    {
        if(index < 0 || index >= values.size())
            return;

        values[index] = (val.has_value()) ? std::any_cast<T>(val) : T{};
    }

    void setValues(const std::any& val) override
    {
        values = (val.has_value()) ? std::any_cast<QVector<T>>(val) : QVector<T>{};
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override
    {
        IEBufferObject::serialize(out, obj);

        const auto& buffer = static_cast<const IEVertexBufferObject&>(obj);

        out << buffer.values
            << buffer.tuple << buffer.stride
            << buffer.offset << buffer.divisor;

        return out;
    }

    QDataStream& deserialize(QDataStream& in, Serializable& obj) override
    {
        IEBufferObject::deserialize(in, obj);

        auto& buffer = static_cast<IEVertexBufferObject&>(obj);

        in >> buffer.values
           >> buffer.tuple >> buffer.stride
           >> buffer.offset >> buffer.divisor;

        return in;
    }
};


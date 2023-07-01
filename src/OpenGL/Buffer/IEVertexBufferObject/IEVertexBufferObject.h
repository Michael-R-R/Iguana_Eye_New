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
    bool isInstance;

public:
    IEVertexBufferObject(QObject* parent = nullptr) :
        IEBufferObject(QOpenGLBuffer::VertexBuffer, parent),
        tuple(0), stride(0), offset(0), divisor(0),
        isInstance(false)
    {

    }

    IEVertexBufferObject(const int t, const int s,
                         const int o, const int d,
                         QObject* parent = nullptr) :
        IEBufferObject(QOpenGLBuffer::VertexBuffer, parent),
        tuple(t), stride(s), offset(o), divisor(d),
        isInstance((d > 0))
    {
        switch(typeid(T).hash_code())
        {
        case typeid(QVector2D).hash_code(): { bufferType = IEBufferType::Vec2; break; }
        case typeid(QVector3D).hash_code(): { bufferType = IEBufferType::Vec3; break; }
        case typeid(QVector4D).hash_code(): { bufferType = IEBufferType::Vec4; break; }
        case typeid(QMatrix4x4).hash_code(): { bufferType = IEBufferType::Mat4; break; }
        default: { bufferType = IEBufferType::Unknown; break; }
        }
    }

    virtual ~IEVertexBufferObject()
    {

    }

    IEVertexBufferObject(const IEVertexBufferObject&) = delete;

    int appendValue(const T& val)
    {
        const int index = values.size();
        values.append(val);
        return index;
    }

    bool removeValue(const int index)
    {
        if(index < 0 || index >= values.size())
            return false;

        const int lastIndex = values.size() - 1;
        values[index] = values[lastIndex];
        values.removeLast();

        return true;
    }

    T* getValue(const int index)
    {
        if(index < 0 || index >= values.size())
            return nullptr;

        return &values[index];
    }

    void setValue(const int index, const T& val)
    {
        if(index < 0 || index >= values.size())
            return;

        values[index] = val;
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
        if(!isInstance)
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

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override
    {
        IEBufferObject::serialize(out, obj);

        const auto& buffer = static_cast<const IEVertexBufferObject&>(obj);

        out << buffer.values
            << buffer.tuple << buffer.stride
            << buffer.offset << buffer.divisor
            << buffer.isInstance;

        return out;
    }

    QDataStream& deserialize(QDataStream& in, Serializable& obj) override
    {
        IEBufferObject::deserialize(in, obj);

        auto& buffer = static_cast<IEVertexBufferObject&>(obj);

        in >> buffer.values
           >> buffer.tuple >> buffer.stride
           >> buffer.offset >> buffer.divisor
           >> buffer.isInstance;

        return in;
    }
};


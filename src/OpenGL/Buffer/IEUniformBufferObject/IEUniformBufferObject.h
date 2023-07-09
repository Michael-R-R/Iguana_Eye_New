#pragma once

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include <any>

#include "IEObject.h"

template<class T>
class IEUniformBufferObject : public IEObject
{
    QVector<T> values;
    QString blockName;
    int bindingPoint;
    int id;

public:
    IEUniformBufferObject(QObject* parent = nullptr) :
        IEObject(parent),
        values(), blockName(""),
        bindingPoint(-1), id(-1)
    {

    }

    IEUniformBufferObject(const QString& blockName,
                          const int bindingPoint,
                          const int size,
                          QObject* parent = nullptr) :
        IEObject(parent),
        values(), blockName(blockName),
        bindingPoint(bindingPoint), id(-1)
    {
        for(int i = 0; i < size; i++)
        {
            this->appendValue(T{});
        }
    }

    virtual ~IEUniformBufferObject()
    {
        this->destroy();
    }

    bool create()
    {
        if(isCreated())
            return false;

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();

        GLuint buffers[] = { (GLuint)id };
        gl->glGenBuffers(1, buffers);

        id = buffers[0];

        return true;
    }

    void destroy()
    {
        if(!isCreated())
            return;

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();

        const GLuint buffers[] = { (GLuint)id };
        gl->glDeleteBuffers(1, buffers);

        id = -1;
    }

    int appendValue(const std::any& val)
    {
        const int index = values.size();

        if(val.has_value())
            values.append(std::any_cast<T>(val));
        else
            values.append(T{});

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

    bool bind()
    {
        if(!isCreated())
            return false;

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();
        gl->glBindBuffer(GL_UNIFORM_BUFFER, id);

        return true;
    }

    bool release()
    {
        if(!isCreated())
            return false;

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();
        gl->glBindBuffer(GL_UNIFORM_BUFFER, 0);

        return true;
    }

    void handleAllocate(bool doRelease = false)
    {
        this->bind();

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();
        gl->glBufferData(GL_UNIFORM_BUFFER, (this->count() * sizeof(T)), values.constData(), GL_STATIC_DRAW);
        gl->glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, id);

        if(doRelease)
            this->release();
    }

    void handleSuballocate(const int offset)
    {
        if(offset < 0 || offset >= values.size())
            return;

        this->bind();

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();
        gl->glBufferSubData(GL_UNIFORM_BUFFER, (offset * sizeof(T)), sizeof(T), &values[offset]);

        this->release();
    }

    void build()
    {
        this->create();
        this->handleAllocate(true);
    }

    bool linkBlock(const int program)
    {
        if(!isCreated() ||
            blockName == "" ||
            bindingPoint < 0)
        {
            return false;
        }

        auto* gl = QOpenGLContext::currentContext()->extraFunctions();

        int blockIndex = gl->glGetUniformBlockIndex(program, blockName.toLocal8Bit().data());
        gl->glUniformBlockBinding(program, blockIndex, bindingPoint);

        return true;
    }

    bool isCreated()
    {
        return (id > -1);
    }

    int count() const
    {
        return values.size();
    }

    std::any getValue(const int index) const
    {
        if(index < 0 || index >= values.size())
            return std::any{};

        return values[index];
    }

    std::any getValues() const
    {
        return values;
    }

    void setValue(const int index, const std::any& val)
    {
        if(index < 0 || index >= values.size())
            return;

        values[index] = (val.has_value()) ? std::any_cast<T>(val) : T{};
    }

    void setValues(const std::any& val)
    {
        values = (val.has_value()) ? std::any_cast<QVector<T>>(val) : QVector<T>{};
    }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override
    {
        IEObject::serialize(out, obj);

        const auto& buffer = static_cast<const IEUniformBufferObject&>(obj);

        // TODO serialize values

        out << buffer.blockName << buffer.bindingPoint;

        return out;
    }

    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override
    {
        IEObject::deserialize(in, obj);

        auto& buffer = static_cast<IEUniformBufferObject&>(obj);
        buffer.values.clear();

        // TODO deserialize values

        in >> buffer.blockName >> buffer.bindingPoint;

        return in;
    }
};


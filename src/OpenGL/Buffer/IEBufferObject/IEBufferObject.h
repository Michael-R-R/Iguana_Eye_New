#pragma once

#include <QOpenGLBuffer>
#include <QVector>

#include "IEObject.h"
#include "IEEnum.h"

class IEBufferObject : public QOpenGLBuffer, public IEObject
{
protected:
    IEBufferType bufferType;
    QOpenGLBuffer::UsagePattern usage;

public:
    IEBufferObject(QOpenGLBuffer::Type type, QObject* parent = nullptr);
    IEBufferObject(const IEBufferObject&) = delete;
    virtual ~IEBufferObject();

    virtual void handleAllocate(const bool doRelease = false) = 0;
    virtual void handleSuballocate(const int index) = 0;
    virtual void build(const int loc = -1) = 0;
    virtual int size() const = 0;

    IEBufferType getBufferType() { return bufferType; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


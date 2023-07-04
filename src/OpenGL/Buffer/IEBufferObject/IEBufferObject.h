#pragma once

#include <QOpenGLBuffer>
#include <QVector>
#include <any>

#include "IEObject.h"
#include "IEEnum.h"

class IEBufferObject : public QOpenGLBuffer, public IEObject
{
protected:
    IEBufferType bufferType;
    QOpenGLBuffer::UsagePattern usage;
    bool isInstanced;

public:
    IEBufferObject(QOpenGLBuffer::Type glType, IEBufferType ieType,
                   bool instanced, QObject* parent = nullptr);
    IEBufferObject(const IEBufferObject&) = delete;
    virtual ~IEBufferObject();

    virtual int appendValue(const std::any& val) = 0;
    virtual bool removeValue(const int index) = 0;
    virtual void handleAllocate(const bool doRelease = false) = 0;
    virtual void handleSuballocate(const int index) = 0;
    virtual void build(const int loc = -1) = 0;
    virtual int count() const = 0;
    virtual std::any getValue(const int index) = 0;
    virtual std::any getValues() const = 0;
    virtual void setValue(const int index, const std::any& val) = 0;
    virtual void setValues(const std::any& val) = 0;

    IEBufferType getBufferType() const { return bufferType; }
    bool getIsInstanced() const { return isInstanced; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


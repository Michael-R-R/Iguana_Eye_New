#pragma once

#include <QVector>

#include "IEBufferObject.h"

class IEIndexBufferObject : public IEBufferObject
{
    QVector<unsigned> values;

public:
    IEIndexBufferObject(QObject* parent = nullptr);
    IEIndexBufferObject(const QVector<unsigned>& vals, QObject* parent = nullptr);
    virtual ~IEIndexBufferObject();

    int appendValue(const std::any& val) override;
    bool removeValue(const int index) override;
    void handleAllocate(const bool doRelease = false) override;
    void handleSuballocate(const int index) override;
    void build(const int loc = -1) override;
    int count() const override;
    std::any getValue(const int index) override;
    std::any getValues() const override;
    void setValue(const int index, const std::any& val) override;
    void setValues(const std::any& val) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};


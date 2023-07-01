#pragma once

#include <QVector>

#include "IEBufferObject.h"

class IEIndexBufferObject : public IEBufferObject
{
    QVector<unsigned> values;

public:
    IEIndexBufferObject(QObject* parent = nullptr);
    virtual ~IEIndexBufferObject();

    int appendValue(const unsigned val);
    bool removeValue(const int index);
    unsigned getValue(const int index);
    void setValue(const int index, const unsigned val);

    void handleAllocate(const bool doRelease = false) override;
    void handleSuballocate(const int index) override;
    void build(const int loc) override;
    int size() const override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


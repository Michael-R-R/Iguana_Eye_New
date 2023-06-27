#pragma once

#include <QString>

#include "IEObject.h"

class IEResource : public IEObject
{
    Q_OBJECT

protected:
    QString name;
    unsigned long long id;

public:
    IEResource(QObject* parent = nullptr);
    IEResource(const IEResource&) = delete;
    virtual ~IEResource();

    bool operator==(const IEResource& other) { return (this->id == other.id); }
    bool operator!=(const IEResource& other) { return (this->id != other.id); }
    bool operator<(const IEResource& other) { return (this->id < other.id); }
    bool operator>(const IEResource& other) { return (this->id > other.id); }

    virtual unsigned long long updateId(const QString& path) = 0;

    const QString& getName() const { return name; }
    unsigned long long getId() const { return id; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

signals:
    void nameUpdated(const unsigned long long id, const QString& path);
};


#pragma once

#include <QString>

#include "IEObject.h"

class IEResource : public IEObject
{
    Q_OBJECT

protected:
    QString filePath;
    unsigned long long id;

public:
    IEResource(QObject* parent = nullptr);
    IEResource(const QString& path, QObject* parent = nullptr);
    IEResource(const IEResource&) = delete;
    virtual ~IEResource();

    bool operator==(const IEResource& other) { return (this->id == other.id); }
    bool operator!=(const IEResource& other) { return (this->id != other.id); }
    bool operator<(const IEResource& other) { return (this->id < other.id); }
    bool operator>(const IEResource& other) { return (this->id > other.id); }

    unsigned long long updatePath(const QString& path);

    const QString& getFilePath() const { return filePath; }
    unsigned long long getId() const { return id; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

signals:
    void pathUpdated(const unsigned long long id, const QString& path);
};


#pragma once

#include <QString>

#include "Serializable.h"

class IEResource : public Serializable
{
protected:
    QString filePath;
    unsigned long long id;
    bool isViewable;

public:
    IEResource();
    IEResource(const QString& path);
    ~IEResource();

    bool operator==(const IEResource& other) { return (this->id == other.id); }
    bool operator!=(const IEResource& other) { return (this->id != other.id); }
    bool operator<(const IEResource& other) { return (this->id < other.id); }
    bool operator>(const IEResource& other) { return (this->id > other.id); }

    unsigned long long updatePath(const QString& path);

    const QString& getFilePath() const { return filePath; }
    unsigned long long getId() const { return id; }
    bool getIsViewable() const { return isViewable; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


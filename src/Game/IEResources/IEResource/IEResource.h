#pragma once

#include <QString>

class IEResource
{
public:
    enum class RsrcType
    {
        Editor, Game
    };

protected:
    QString filePath;
    unsigned long long id;
    RsrcType type;

public:
    IEResource(const QString& path, const unsigned long long resourceId);
    ~IEResource();

    bool operator==(const IEResource& other) { return (this->id == other.id); }
    bool operator!=(const IEResource& other) { return (this->id != other.id); }
    bool operator<(const IEResource& other) { return (this->id < other.id); }
    bool operator>(const IEResource& other) { return (this->id > other.id); }

    const QString& getFilePath() const { return filePath; }
    unsigned long long getId() const { return id; }
    RsrcType getType() const { return type; }

    void setFilePath(const QString& val) { filePath = val; }
    void setId(const unsigned long long val) { id = val; }
    void setType(const RsrcType val) { type = val; }
};


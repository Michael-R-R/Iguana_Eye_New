#pragma once

#include <QDataStream>

#include "IEResource.h"

class IEEntity;

class IEScript : public IEResource
{

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long id);
    IEScript(const IEScript& other);
    ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    void attachEntity(const IEEntity entity);
    void start();
    void update();

    friend QDataStream& operator<<(QDataStream& out, const IEScript& script)
    {
        out << script.filePath << script.id << script.type;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScript& script)
    {
        in >> script.filePath << script.id << script.type;

        return in;
    }
};


#pragma once

#include <QDataStream>

#include "IEResource.h"

class IEScript : public IEResource
{

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long resourceId);
    IEScript(const IEScript& other);
    ~IEScript() {}

    bool operator==(const IEScript& other) { return IEResource::operator ==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator !=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator <(other); }
    bool operator>(const IEScript& other) { return IEResource::operator >(other); }

    friend QDataStream& operator<<(QDataStream& out, const IEScript& script)
    {
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScript& script)
    {
        return in;
    }
};


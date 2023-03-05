#pragma once

#include <QDataStream>
#include <QString>
#include <QJSValue>

#include "IEResource.h"

class QJSEngine;

class IEScript : public IEResource
{
    QString code;

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long resourceId);
    IEScript(const IEScript& other);
    ~IEScript() {}

    bool operator==(const IEScript& other) { return IEResource::operator ==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator !=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator <(other); }
    bool operator>(const IEScript& other) { return IEResource::operator >(other); }

    QJSValue call(QJSEngine* engine);

    friend QDataStream& operator<<(QDataStream& out, const IEScript& script)
    {
        out << script.filePath << script.id << script.type;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScript& script)
    {
        in >> script.filePath >> script.id >> script.type;

        return in;
    }
};


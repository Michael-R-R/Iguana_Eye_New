#pragma once

#include <QDataStream>
#include <QString>
#include <QJSValue>

#include "IEResource.h"

class QJSEngine;
class IEEntity;

class IEScript : public IEResource
{
    QJSValue jsAttachEntityFunc;
    QJSValue jsStartFunc;
    QJSValue jsUpdateFunc;

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long id);
    IEScript(const IEScript& other);
    ~IEScript() {}

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    void import(QJSEngine* engine);
    QJSValue attachEntity(const IEEntity entity);
    QJSValue start();
    QJSValue update();

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


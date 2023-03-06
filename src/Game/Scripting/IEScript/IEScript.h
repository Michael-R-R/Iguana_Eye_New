#pragma once

#include <QDataStream>
#include <QString>
#include <QJSValue>

class QJSEngine;
class IEEntity;

class IEScript
{
    QString filePath;

    QJSValue jsAttachEntityFunc;
    QJSValue jsStartFunc;
    QJSValue jsUpdateFunc;

public:
    IEScript();
    IEScript(const QString& path);
    IEScript(const IEScript& other);
    ~IEScript() {}

    void import(QJSEngine* engine);
    QJSValue attachEntity(const IEEntity entity);
    QJSValue start();
    QJSValue update();

    friend QDataStream& operator<<(QDataStream& out, const IEScript& script)
    {
        out << script.filePath;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScript& script)
    {
        in >> script.filePath;

        return in;
    }
};


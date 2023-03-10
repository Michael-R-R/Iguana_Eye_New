#pragma once

#include <QDataStream>
#include <QMap>
#include <QString>
#include <sol/sol.hpp>

class IEScript;

class IEScriptData
{
protected:
    QMap<QString, QString> strMap;
    QMap<QString, float> numMap;
    QMap<QString, bool> boolMap;

public:
    IEScriptData();
    IEScriptData(const IEScriptData& other);
    ~IEScriptData() {}

    void fromScript(sol::environment& env);
    void toScript(sol::environment& env);

    friend QDataStream& operator<<(QDataStream& out, const IEScriptData& data)
    {
        out << data.strMap << data.numMap << data.boolMap;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScriptData& data)
    {
        in >> data.strMap >> data.numMap >> data.boolMap;

        return in;
    }
};


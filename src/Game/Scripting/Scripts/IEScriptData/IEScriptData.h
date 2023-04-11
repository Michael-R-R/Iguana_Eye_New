#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <sol/sol.hpp>

class IEScriptData
{
protected:
    QVector<QString> tableNames;
    QVector<QMap<QString, QString>> strTableVals;
    QVector<QMap<QString, float>> numTableVals;
    QVector<QMap<QString, bool>> boolTableVals;

public:
    IEScriptData();
    IEScriptData(const IEScriptData& other);
    ~IEScriptData() {}

    void clear();
    void fromScript(sol::environment& env);
    void toScript(sol::environment& env);

private:
    void fromScriptHelper(sol::table& table, const QString& tableName = "");

public:
    friend QDataStream& operator<<(QDataStream& out, const IEScriptData& data)
    {
        out << data.tableNames << data.strTableVals << data.numTableVals << data.boolTableVals;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScriptData& data)
    {
        in >> data.tableNames >> data.strTableVals >> data.numTableVals >> data.boolTableVals;

        return in;
    }
};


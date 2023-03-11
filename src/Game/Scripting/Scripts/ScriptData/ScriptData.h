#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <sol/sol.hpp>

class ScriptData
{
protected:
    QVector<QString> tableNames;
    QVector<QMap<QString, QString>> strTableVals;
    QVector<QMap<QString, float>> numTableVals;
    QVector<QMap<QString, bool>> boolTableVals;

public:
    ScriptData();
    ScriptData(const ScriptData& other);
    ~ScriptData() {}

    void clear();
    void fromScript(sol::environment& env);
    void toScript(sol::environment& env);

private:
    void fromScriptHelper(sol::table& table, const QString& tableName = "");

public:
    friend QDataStream& operator<<(QDataStream& out, const ScriptData& data)
    {
        out << data.tableNames << data.strTableVals << data.numTableVals << data.boolTableVals;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, ScriptData& data)
    {
        in >> data.tableNames >> data.strTableVals >> data.numTableVals >> data.boolTableVals;

        return in;
    }
};


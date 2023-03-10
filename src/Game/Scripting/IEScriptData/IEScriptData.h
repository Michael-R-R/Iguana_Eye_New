#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <sol/sol.hpp>

class IEScript;

class IEScriptData
{
    struct Table
    {
        QVector<QString> name;
        QVector<QMap<QString, QString>> strTableVals;
        QVector<QMap<QString, float>> numTableVals;
        QVector<QMap<QString, bool>> boolTableVals;

        friend QDataStream& operator<<(QDataStream& out, const Table& data)
        {
            out << data.name << data.strTableVals << data.numTableVals << data.boolTableVals;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Table& data)
        {
            in >> data.name >> data.strTableVals >> data.numTableVals >> data.boolTableVals;

            return in;
        }

        void clear()
        {
            name.clear();
            strTableVals.clear();
            numTableVals.clear();
            boolTableVals.clear();
        }
    };

    Table data;

public:
    IEScriptData();
    IEScriptData(const IEScriptData& other);
    ~IEScriptData() {}

    void fromScript(sol::environment& env);
    void toScript(sol::environment& env);

private:
    void fromScriptHelper(sol::table& table, const QString& tableName = "");

public:
    friend QDataStream& operator<<(QDataStream& out, const IEScriptData& scriptData)
    {
        out << scriptData.data;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScriptData& scriptData)
    {
        in >> scriptData.data;

        return in;
    }
};


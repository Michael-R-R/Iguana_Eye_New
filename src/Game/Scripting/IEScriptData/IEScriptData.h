#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <sol/sol.hpp>

#include "Serializable.h"

class IEScriptData : public Serializable
{
protected:
    QVector<QString> tableNames;
    QVector<QMap<QString, QString>> strTableVals;
    QVector<QMap<QString, float>> numTableVals;
    QVector<QMap<QString, bool>> boolTableVals;

public:
    IEScriptData();
    IEScriptData(const IEScriptData&) = delete;
    virtual ~IEScriptData();

    void clear();
    void fromScript(sol::environment& env);
    void toScript(sol::environment& env);

private:
    void fromScriptHelper(sol::table& table, const QString& tableName = "");

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


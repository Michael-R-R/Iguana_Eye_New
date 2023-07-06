#include "IEScriptData.h"

IEScriptData::IEScriptData() :
    tableNames(), strTableVals(),
    numTableVals(), boolTableVals()
{

}

IEScriptData::~IEScriptData()
{

}

void IEScriptData::clear()
{
    tableNames.clear();
    strTableVals.clear();
    numTableVals.clear();
    boolTableVals.clear();
}

void IEScriptData::fromScript(sol::environment& env)
{
    if(!env)
        return;

    clear();
    fromScriptHelper(env);
}

void IEScriptData::toScript(sol::environment& env)
{
    if(!env)
        return;

    sol::environment table = env;

    for(int i = 0; i < tableNames.size(); i++)
    {
        if(i > 0) { table = table[tableNames[i].toStdString()]; }

        QMapIterator<QString, QString> it1(strTableVals[i]);
        while(it1.hasNext()) { it1.next(); table[it1.key().toStdString()] = it1.value().toStdString(); }

        QMapIterator<QString, float> it2(numTableVals[i]);
        while(it2.hasNext()) { it2.next(); table[it2.key().toStdString()] = it2.value(); }

        QMapIterator<QString, bool> it3(boolTableVals[i]);
        while(it3.hasNext()) { it3.next(); table[it3.key().toStdString()] = it3.value(); }
    }
}

void IEScriptData::fromScriptHelper(sol::table& table, const QString& tableName)
{
    int index = tableNames.size();

    tableNames.append(tableName);
    strTableVals.append(QMap<QString, QString>());
    numTableVals.append(QMap<QString, float>());
    boolTableVals.append(QMap<QString, bool>());

    for(const auto& i : table)
    {
        QString key = QString(i.first.as<const char*>());

        sol::type type = i.second.get_type();
        switch(type)
        {
        case sol::type::string:
        {
            const QString value = QString(i.second.as<const char*>());
            strTableVals[index][key] = value;
            break;
        }
        case sol::type::number:
        {
            float value = i.second.as<float>();
            numTableVals[index][key] = value;
            break;
        }
        case sol::type::boolean:
        {
            bool value = i.second.as<bool>();
            boolTableVals[index][key] = value;
            break;
        }
        case sol::type::table:
        {
            sol::table tempTable = i.second.as<sol::table>();
            fromScriptHelper(tempTable, key);
            break;
        }
        default: { break; }
        }
    }
}

QDataStream& IEScriptData::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& data = static_cast<const IEScriptData&>(obj);

    out << data.tableNames << data.strTableVals
        << data.numTableVals << data.boolTableVals;

    return out;
}

QDataStream& IEScriptData::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& data = static_cast<IEScriptData&>(obj);

    in >> data.tableNames >> data.strTableVals
       >> data.numTableVals >> data.boolTableVals;

    return in;
}

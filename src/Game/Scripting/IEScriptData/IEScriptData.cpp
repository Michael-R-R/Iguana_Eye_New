#include "IEScriptData.h"

IEScriptData::IEScriptData() :
    data()
{

}

IEScriptData::IEScriptData(const IEScriptData& other) :
    data(other.data)
{

}

void IEScriptData::fromScript(sol::environment& env)
{
    data.clear();

    fromScriptHelper(env);
}

void IEScriptData::toScript(sol::environment& env)
{
    sol::table table = env;

    for(int i = 0; i < data.name.size(); i++)
    {
        if(i > 0)
            table = table[data.name[i].toStdString()];

        QMapIterator<QString, QString> it1(data.strTableVals[i]);
        while(it1.hasNext()) { it1.next(); table[it1.key().toStdString()] = it1.value().toStdString(); }

        QMapIterator<QString, float> it2(data.numTableVals[i]);
        while(it2.hasNext()) { it2.next(); table[it2.key().toStdString()] = it2.value(); }

        QMapIterator<QString, bool> it3(data.boolTableVals[i]);
        while(it3.hasNext()) { it3.next(); table[it3.key().toStdString()] = it3.value(); }
    }
}

void IEScriptData::fromScriptHelper(sol::table& table, const QString& tableName)
{
    int index = data.name.size();

    data.name.append(tableName);
    data.strTableVals.append(QMap<QString, QString>());
    data.numTableVals.append(QMap<QString, float>());
    data.boolTableVals.append(QMap<QString, bool>());

    for(const auto& i : table)
    {
        QString key = QString(i.first.as<const char*>());

        sol::type type = i.second.get_type();
        switch(type)
        {
        case sol::type::string:
        {
            const QString value = QString(i.second.as<const char*>());
            data.strTableVals[index][key] = value;
            break;
        }
        case sol::type::number:
        {
            float value = i.second.as<float>();
            data.numTableVals[index][key] = value;
            break;
        }
        case sol::type::boolean:
        {
            bool value = i.second.as<bool>();
            data.boolTableVals[index][key] = value;
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

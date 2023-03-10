#include "IEScriptData.h"

IEScriptData::IEScriptData() :
    strMap(), numMap(), boolMap()
{

}

IEScriptData::IEScriptData(const IEScriptData& other) :
    strMap(other.strMap), numMap(other.numMap), boolMap(other.boolMap)
{

}

void IEScriptData::fromScript(sol::environment& env)
{
    sol::table table = env;
    for(const auto& i : table)
    {
        const QString key = QString(i.first.as<const char*>());

        sol::type type = i.second.get_type();
        switch(type)
        {
        case sol::type::string:
        {
            const QString value = QString(i.second.as<const char*>());
            strMap[key] = value;
            break;
        }
        case sol::type::number:
        {
            float value = i.second.as<float>();
            numMap[key] = value;
            break;
        }
        case sol::type::boolean:
        {
            bool value = i.second.as<bool>();
            boolMap[key] = value;
            break;
        }
        default: { break; }
        }
    }
}

void IEScriptData::toScript(sol::environment& env)
{
    QMapIterator<QString, QString> it1(strMap);
    while(it1.hasNext()) { it1.next(); env[it1.key().toStdString()] = it1.value().toStdString(); }

    QMapIterator<QString, float> it2(numMap);
    while(it2.hasNext()) { it2.next(); env[it2.key().toStdString()] = it2.value(); }

    QMapIterator<QString, bool> it3(boolMap);
    while(it3.hasNext()) { it3.next(); env[it3.key().toStdString()] = it3.value(); }
}

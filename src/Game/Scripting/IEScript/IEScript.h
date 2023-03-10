#pragma once

#include <QDataStream>
#include <sol/sol.hpp>

#include "IEResource.h"
#include "IEScriptData.h"

class IEScript : public IEResource
{
    sol::environment env;

    sol::function startFunc;
    sol::function updateFunc;
    sol::function sleepFunc;

    IEScriptData scriptData;

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long id);
    IEScript(const IEScript& other);
    ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    void create(sol::state& lua);
    void start(const int id);
    void update(const int id);
    void sleep(const int id);

    sol::object value(const char* name);
    sol::object func(const char* name, sol::variadic_args args);

    void dataFromScript() { scriptData.fromScript(env); }
    void dataToScript() { scriptData.toScript(env); }

    const sol::environment& getEnviroment() const { return env; }

    friend QDataStream& operator<<(QDataStream& out, const IEScript& script)
    {
        const_cast<IEScript&>(script).dataFromScript();

        out << script.filePath << script.id << script.type << script.scriptData;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScript& script)
    {
        in >> script.filePath >> script.id >> script.type >> script.scriptData;

        return in;
    }
};


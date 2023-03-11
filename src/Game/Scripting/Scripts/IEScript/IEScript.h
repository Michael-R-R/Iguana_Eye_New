#pragma once

#include <QDataStream>
#include <sol/sol.hpp>

#include "IEResource.h"
#include "ScriptData.h"

class IEScript : public IEResource
{
protected:
    sol::environment env;
    ScriptData scriptData;

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long id);
    ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    virtual void create(sol::state& lua) = 0;

    void dataFromScript();
    void dataToScript();

    sol::object value(const char* name);
    sol::object func(const char* name, sol::variadic_args args);
};


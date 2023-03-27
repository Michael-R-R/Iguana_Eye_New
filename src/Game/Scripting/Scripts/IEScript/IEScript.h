#pragma once

#include <QDataStream>
#include <sol/sol.hpp>

#include "IEResource.h"

class IEScript : public IEResource
{
protected:
    sol::environment env;
    bool isValid;

public:
    IEScript();
    IEScript(const QString& path, const unsigned long long id);
    ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    virtual bool initalize(sol::state& lua) = 0;

    bool getIsValid() const { return isValid; }

    sol::object value(const char* name) const;
    sol::object getFunc(const char* name) const;
    sol::object callFunc(const char* name, sol::variadic_args args) const;
};


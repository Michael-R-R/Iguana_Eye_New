#pragma once

#include <QDataStream>
#include <sol/sol.hpp>

#include "IEResource.h"

class IEScript : public IEResource
{
protected:
    sol::environment env;

public:
    IEScript();
    IEScript(const QString& path);
    IEScript(const IEScript&) = delete;
    ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    virtual bool initalize(sol::state& lua) = 0;

    sol::object value(const char* name) const;
    sol::object getFunc(const char* name) const;
    sol::object callFunc(const char* name, sol::variadic_args args) const;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


#pragma once

#include <QDataStream>
#include <sol/sol.hpp>

#include "IEFileResource.h"
#include "IEScriptData.h"

class IEEntity;

class IEScript : public IEFileResource
{
protected:
    sol::environment env;

    sol::function initFunc;
    sol::function startFunc;
    sol::function updateFunc;
    sol::function wakeFunc;
    sol::function sleepFunc;
    sol::function onTriggerEnterFunc;
    sol::function onTriggerLeaveFunc;

    IEScriptData scriptData;

public:
    IEScript(QObject* parent = nullptr);
    IEScript(const QString& path, QObject* parent = nullptr);
    IEScript(const IEScript&) = delete;
    virtual ~IEScript();

    bool operator==(const IEScript& other) { return IEResource::operator==(other); }
    bool operator!=(const IEScript& other) { return IEResource::operator!=(other); }
    bool operator<(const IEScript& other) { return IEResource::operator<(other); }
    bool operator>(const IEScript& other) { return IEResource::operator>(other); }

    virtual bool initalize(sol::state& lua, const IEEntity& entity);
    virtual void start();
    virtual void update();
    virtual void wake();
    virtual void sleep();
    virtual void onTriggerEnter(const IEEntity& other);
    virtual void onTriggerLeave(const IEEntity& other);

    virtual void dataFrom();
    virtual void dataTo();

    sol::function getCustomFunc(const char* name) const;

    sol::object value(const char* name) const;
    sol::object getFunc(const char* name) const;
    sol::object callFunc(const char* name, sol::variadic_args args) const;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};


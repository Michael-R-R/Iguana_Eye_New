#pragma once

#include <QString>
#include <sol/sol.hpp>

#include "IEScript.h"
#include "ScriptData.h"
#include "IEEntity.h"

class IEEntityScript : public IEScript
{
    sol::function startFunc;
    sol::function updateFunc;
    sol::function wakeFunc;
    sol::function sleepFunc;
    sol::function onTriggerEnterFunc;
    sol::function onTriggerLeaveFunc;

    ScriptData scriptData;

public:
    IEEntityScript();
    IEEntityScript(const QString& path);
    IEEntityScript(const IEEntityScript&) = delete;
    ~IEEntityScript();

    bool operator==(const IEEntityScript& other) { return IEScript::operator==(other); }
    bool operator!=(const IEEntityScript& other) { return IEScript::operator!=(other); }
    bool operator<(const IEEntityScript& other) { return IEScript::operator<(other); }
    bool operator>(const IEEntityScript& other) { return IEScript::operator>(other); }

    bool initalize(sol::state& lua) override;

    void start(const IEEntity entity) const;
    void update() const;
    void wake() const;
    void sleep() const;
    void onTriggerEnter(const IEEntity& otherEntity) const;
    void onTriggerLeave(const IEEntity& otherEntity) const;

    void dataFromScript();
    void dataToScript();

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};


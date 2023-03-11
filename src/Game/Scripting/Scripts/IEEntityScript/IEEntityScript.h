#pragma once

#include <QDataStream>
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

    ScriptData scriptData;

public:
    IEEntityScript();
    IEEntityScript(const QString& path, const unsigned long long id);
    ~IEEntityScript();

    bool operator==(const IEEntityScript& other) { return IEScript::operator==(other); }
    bool operator!=(const IEEntityScript& other) { return IEScript::operator!=(other); }
    bool operator<(const IEEntityScript& other) { return IEScript::operator<(other); }
    bool operator>(const IEEntityScript& other) { return IEScript::operator>(other); }

    bool initalize(sol::state &lua) override;
    void start(const IEEntity entity);
    void update();
    void wake();
    void sleep();

    void dataFromScript();
    void dataToScript();

    friend QDataStream& operator<<(QDataStream& out, const IEEntityScript& script)
    {
        const_cast<IEEntityScript&>(script).dataFromScript();

        out << script.filePath << script.id << script.type << script.scriptData;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEEntityScript& script)
    {
        in >> script.filePath >> script.id >> script.type >> script.scriptData;

        return in;
    }
};


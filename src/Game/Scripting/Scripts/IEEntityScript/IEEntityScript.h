#pragma once

#include <QDataStream>
#include <QString>
#include <sol/sol.hpp>

#include "IEScript.h"

class IEEntityScript : public IEScript
{
    sol::function startFunc;
    sol::function updateFunc;
    sol::function sleepFunc;

public:
    IEEntityScript();
    IEEntityScript(const QString& path, const unsigned long long id);
    ~IEEntityScript();

    void create(sol::state &lua) override;
    void start(const int id);
    void update(const int id);
    void sleep(const int id);

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


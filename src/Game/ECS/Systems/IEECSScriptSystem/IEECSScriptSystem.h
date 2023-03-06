#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QSet>

#include "IEECSSystem.h"
#include "IEScript.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class QJSEngine;

class IEECSScriptSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QMap<unsigned long long, IEScript*>> scriptCollection;
        QVector<QSet<unsigned long long>> disabledScripts;
        QVector<QSet<unsigned long long>> activeScripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.disabledScripts << data.activeScripts;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.disabledScripts >> data.activeScripts;

            return in;
        }
    };

    Data data;

public:
    IEECSScriptSystem();
    ~IEECSScriptSystem() {}

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void importAllScripts(QJSEngine* engine);
    void enableAllScripts();
    void disableAllScripts();

    void enableScript(const int index, const unsigned long long id);
    void disableScript(const int index, const unsigned long long id);

    void addScript(const int index, IEScript* script);
    void removeScript(const int index, const unsigned long long id);
    bool isScriptAttached(const int index, const unsigned long long id);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEECSScriptSystem& system)
    {
        out << system.entityMap << system.data;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSScriptSystem& system)
    {
        in >> system.entityMap >> system.data;

        return in;
    }
};


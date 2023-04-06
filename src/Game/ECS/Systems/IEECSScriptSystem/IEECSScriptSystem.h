#pragma once

#include <QVector>
#include <QMap>
#include <QSet>

#include "IEECSSystem.h"
#include "IEEntityScript.h"

class IEGame;
class ECSOnUpdateEvent;

class IEECSScriptSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QMap<unsigned long long, IEEntityScript>> scriptCollection;
        QVector<QSet<unsigned long long>> sleepingScripts;
        QVector<QSet<unsigned long long>> awakenedScripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.scriptCollection << data.sleepingScripts << data.awakenedScripts;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.scriptCollection >> data.sleepingScripts >> data.awakenedScripts;

            return in;
        }
    };

    Data data;

public:
    IEECSScriptSystem(IEGame& game);
    ~IEECSScriptSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void play(IEGame& game) override;
    void stop(IEGame& game) override;

    bool initalizeScript(const int index, const unsigned long long id, sol::state& lua);
    void startScript(const int index, const unsigned long long id);
    void wakeScript(const int index, const unsigned long long id);
    void sleepScript(const int index, const unsigned long long id);
    void clearSleepingScripts();
    void clearAwakenScripts();

    void attachScript(const int index, const IEEntityScript& script);
    void removeScript(const int index, const unsigned long long id);

    bool hasScript(const int index, const unsigned long long id);
    bool isScriptValid(const int index, const unsigned long long id);

    IEScript* getScript(const int index, const unsigned long long id);
    IEScript* getScript(const int index, const char* name);

private:
    void deserializeScripts();
    void removeAll();
    void removeAll(const int index);

private slots:
    void callOnTriggerEnter(const IEEntity& triggerEntity, const IEEntity& otherEntity);
    void callOnTriggerLeave(const IEEntity& triggerEntity, const IEEntity& otherEntity);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};


#pragma once

#include <QSharedPointer>
#include <QVector>
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
        QVector<QMap<unsigned long long, QSharedPointer<IEEntityScript>>> scriptCollection;
        QVector<QSet<unsigned long long>> sleepingScripts;
        QVector<QSet<unsigned long long>> awakenedScripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.sleepingScripts << data.awakenedScripts;
            out << (int)data.scriptCollection.size();

            foreach (auto i, data.scriptCollection)
            {
                out << (int)i.size();

                foreach(auto j, i)
                {
                    out << *j;
                }
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            data.scriptCollection.clear();

            int vecSize = 0;
            in >> data.entity >> data.sleepingScripts >> data.awakenedScripts;
            in >> vecSize;

            for(int i = 0; i < vecSize; i++)
            {
                QMap<unsigned long long, QSharedPointer<IEEntityScript>> tempMap;

                int mapSize = 0;
                in >> mapSize;

                for(int j = 0; j < mapSize; j++)
                {
                    auto script = QSharedPointer<IEEntityScript>::create();
                    in >> *script;

                    tempMap.insert(script->getId(), script);
                }

                data.scriptCollection.append(tempMap);
            }

            return in;
        }
    };

    Data data;

public:
    IEECSScriptSystem(QObject* parent = nullptr);
    ~IEECSScriptSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent& event) override;
    void initalize() override;
    void reset() override;

    void wakeScript(const int index, const unsigned long long id);
    void sleepScript(const int index, const unsigned long long id);
    void clearSleepingScripts();
    void clearAwakenScripts();

    void attachScript(const int index, const QSharedPointer<IEEntityScript> script);
    void removeScript(const int index, const unsigned long long id);

    bool hasScript(const int index, const unsigned long long id);

    QSharedPointer<IEEntityScript> getScript(const int index, const unsigned long long id);
    QSharedPointer<IEEntityScript> getScript(const int index, const char* name);

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


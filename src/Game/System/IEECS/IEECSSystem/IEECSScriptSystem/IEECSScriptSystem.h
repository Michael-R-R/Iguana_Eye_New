#pragma once

#include <QVector>
#include <QHash>
#include <QSet>

#include "IEECSSystem.h"
#include "IEScript.h"

class IEGame;
class IEScriptEngine;

class IEECSScriptSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data : public IEObject
    {
        QVector<IEEntity> entity;
        QVector<QHash<uint64_t, IEScript*>> scripts;
        QVector<QSet<uint64_t>> sleepingScripts;
        QVector<QSet<uint64_t>> awakenedScripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.sleepingScripts << data.awakenedScripts;
            out << (int)data.scripts.size();

            foreach (auto i, data.scripts)
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
            int vecSize = 0;
            in >> data.entity >> data.sleepingScripts >> data.awakenedScripts;
            in >> vecSize;

            data.scripts.clear();
            for(int i = 0; i < vecSize; i++)
            {
                QHash<uint64_t, IEScript*> tempMap;

                int mapSize = 0;
                in >> mapSize;

                for(int j = 0; j < mapSize; j++)
                {
                    auto* script = new IEScript(&data);

                    in >> *script;

                    tempMap.insert(script->getId(), script);
                }

                data.scripts.append(tempMap);
            }

            return in;
        }
    };

    Data data;

    IEScriptEngine* sEngine;

public:
    IEECSScriptSystem(QObject* parent = nullptr);
    ~IEECSScriptSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    void onDeserialize(const IEGame& game) override;
    void onUpdateFrame() override;

    void initAll();
    void startAll();
    void wakeAll();
    void sleepAll();
    void init(const int index, const uint64_t id);
    void start(const int index, const uint64_t id);
    void wake(const int index, const uint64_t id);
    void sleep(const int index, const uint64_t id);

    void attach(const int index, IEScript* script);
    void remove(const int index, const uint64_t id);

    bool hasScript(const int index, const uint64_t id);

    IEScript* getScript(const int index, const uint64_t id);
    IEScript* getScript(const int index, const char* name);

private:
    void cacheScripts();
    void decacheScripts();
    void removeAll();
    void removeAll(const int index);

private slots:
    void callOnTriggerEnter(const IEEntity& triggerEntity, const IEEntity& otherEntity);
    void callOnTriggerLeave(const IEEntity& triggerEntity, const IEEntity& otherEntity);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};


#pragma once

#include <QVector>
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
        QVector<QMap<unsigned long long, IEScript*>> scripts;
        QVector<QSet<unsigned long long>> sleepingScripts;
        QVector<QSet<unsigned long long>> awakenedScripts;

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
            foreach (auto& collection, data.scripts)
            {
                foreach (auto* i, collection)
                {
                    delete i;
                    i = nullptr;
                }
            }
            data.scripts.clear();

            int vecSize = 0;
            in >> data.entity >> data.sleepingScripts >> data.awakenedScripts;
            in >> vecSize;

            for(int i = 0; i < vecSize; i++)
            {
                QMap<unsigned long long, IEScript*> tempMap;

                int mapSize = 0;
                in >> mapSize;

                for(int j = 0; j < mapSize; j++)
                {
                    auto script = new IEScript(&data);
                    in >> *script;

                    tempMap.insert(script->getId(), script);
                }

                data.scripts.append(tempMap);
            }

            return in;
        }
    };

    Data data;

    IEScriptEngine* scriptEngine;

public:
    IEECSScriptSystem(QObject* parent = nullptr);
    ~IEECSScriptSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void onUpdateFrame() override;

    void wakeScript(const int index, const unsigned long long id);
    void sleepScript(const int index, const unsigned long long id);
    void clearSleepingScripts();
    void clearAwakenScripts();

    void attachScript(const int index, IEScript* script);
    void removeScript(const int index, const unsigned long long id);

    bool hasScript(const int index, const unsigned long long id);

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


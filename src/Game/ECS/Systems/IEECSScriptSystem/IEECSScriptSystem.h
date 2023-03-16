#pragma once

#include <QVector>
#include <QMap>
#include <QSet>

#include "IEECSSystem.h"
#include "IEEntityScript.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEScriptEngine;

class IEECSScriptSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QMap<unsigned long long, IEEntityScript>> scriptCollection;
        QVector<QSet<unsigned long long>> sleepingScripts;
        QVector<QSet<unsigned long long>> awakenedScripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.sleepingScripts << data.awakenedScripts;

            out << (int)data.scriptCollection.size();

            for(int i = 1; i < data.scriptCollection.size(); i++)
            {
                out << (int)data.scriptCollection[i].size();

                QMapIterator<unsigned long long, IEEntityScript> it(data.scriptCollection[i]);
                while(it.hasNext())
                {
                    it.next();
                    out << it.key() << it.value();
                }
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.sleepingScripts >> data.awakenedScripts;

            int size = 0;
            in >> size;

            for(int i = 1; i < size; i++)
            {
                int collectionSize = 0;
                in >> collectionSize;

                data.scriptCollection.append(QMap<unsigned long long, IEEntityScript>());

                for(int j = 0; j < collectionSize; j++)
                {
                    unsigned long long key = 0;
                    IEEntityScript value;

                    in >> key >> value;

                    data.scriptCollection[i][key] = value;
                }
            }

            return in;
        }
    };

    Data data;

    // DOES NOT OWN THIS POINTER
    IEScriptEngine* scriptEngine;

public:
    IEECSScriptSystem();
    ~IEECSScriptSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void initAllScripts();
    void startAllScripts();
    bool initalizeScript(const int index, const unsigned long long id);
    void startScript(const int index, const unsigned long long id);
    void wakeScript(const int index, const unsigned long long id);
    void sleepScript(const int index, const unsigned long long id);
    void clearSleepingScripts();
    void clearAwakenScripts();

    void addScript(const int index, const IEEntityScript& script);
    void removeScript(const int index, const unsigned long long id);

    bool hasScript(const int index, const unsigned long long id);
    bool isScriptValid(const int index, const unsigned long long id);

    IEScript* getScript(const int index, const unsigned long long id);
    IEScript* getScript(const int index, const char* name);

private:
    void deserializeScripts();
    void removeAll();
    void removeAll(const int index);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};


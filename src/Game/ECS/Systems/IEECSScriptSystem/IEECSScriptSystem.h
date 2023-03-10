#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QSet>

#include "IEECSSystem.h"
#include "IEScript.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEScriptEngine;

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

            out << (int)data.scriptCollection.size();
            for(int i = 1; i < data.scriptCollection.size(); i++)
            {
                out << (int)data.scriptCollection[i].size();
                QMapIterator<unsigned long long, IEScript*> it(data.scriptCollection[i]);
                while(it.hasNext())
                {
                    it.next();
                    out << it.key() << *it.value();
                }
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.disabledScripts >> data.activeScripts;

            int size = 0;
            in >> size;

            for(int i = 1; i < size; i++)
            {
                data.scriptCollection.append(QMap<unsigned long long, IEScript*>());

                int collectionSize = 0;
                in >> collectionSize;
                for(int j = 0; j < collectionSize; j++)
                {
                    unsigned long long key = 0;
                    IEScript* value = new IEScript();

                    in >> key >> *value;

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

    void createAllScripts();
    void enableAllScripts();
    void disableAllScripts();

    void enableScript(const int index, const unsigned long long id);
    void disableScript(const int index, const unsigned long long id);

    void addScript(const int index, IEScript* script);
    void removeScript(const int index, const unsigned long long id);
    bool isScriptAttached(const int index, const unsigned long long id);

private:
    void clearAll();
    void clearAtIndex(const int index);

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


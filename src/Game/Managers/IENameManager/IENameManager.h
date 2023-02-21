#pragma once

#include <QDataStream>
#include <tuple>

#include "IEManager.h"

class GameStartEvent;

class IENameManager : public IEManager<QString>
{
    Q_OBJECT

public:
    IENameManager(QObject* parent = nullptr);
    ~IENameManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, QString* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IENameManager& manager)
    {
        auto& resources = manager.getResourceContainer()->getResources();

        out << (int)resources.size();

        QMapIterator<unsigned long long, QString*> it(resources);
        while(it.hasNext())
        {
            it.next();
            out << it.key() << *it.value();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IENameManager& manager)
    {
        int size = 0;
        in >> size;

        unsigned long long id = 0;
        QString str = "";

        for(int i = 0; i < size; i++)
        {
            in >> id >> str;

            manager.add(id, new QString(str));
        }

        return in;
    }
};

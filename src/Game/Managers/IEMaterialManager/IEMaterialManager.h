#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEMaterial.h"

class GameStartEvent;

class IEMaterialManager: public IEManager<IEMaterial>
{
    Q_OBJECT

public:
    IEMaterialManager(QObject* parent = nullptr);
    ~IEMaterialManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEMaterial* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMaterialManager& manager)
    {


        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterialManager& manager)
    {


        return in;
    }
};

#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEShader.h"

class GameStartEvent;

class IEShaderManager : public IEManager<IEShader>
{
    Q_OBJECT

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEShader* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllShaders();

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEShaderManager& manager)
    {
        out << *manager.resourceContainer;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEShaderManager& manager)
    {
        in >> *manager.resourceContainer;
        return in;
    }
};

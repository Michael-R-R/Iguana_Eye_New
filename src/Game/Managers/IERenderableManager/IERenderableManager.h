#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IERenderable.h"

class GameStartEvent;
class IEShader;

class IERenderableManager : public IEManager<IERenderable>
{
    Q_OBJECT

public:
    IERenderableManager(QObject* parent = nullptr);
    ~IERenderableManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IERenderable* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllRenderables(const GameStartEvent& event);

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IERenderableManager& manager)
    {


        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderableManager& manager)
    {


        return in;
    }
};

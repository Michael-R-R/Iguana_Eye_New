#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IESerialize.h"
#include "IERenderable.h"

class GameStartEvent;
class IEShader;

class IERenderableManager : public IEManager<IERenderable>
{
    Q_OBJECT

public:
    IERenderableManager();
    ~IERenderableManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, std::unique_ptr<IERenderable> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllRenderables(const GameStartEvent& event);

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IERenderableManager& manager)
    {
        const auto* resources = manager.getResourceContainer().getResources();

        out << (int)resources->size();

        for(auto& item : *resources)
        {
            if(item.second->getIsEdited() && item.second->getType() == IEResource::Type::Game)
            {
                const QString& filePath = item.second->getFilePath();
                if(!IEFile::doesPathExist(filePath))
                    IEFile::makePath(filePath);

                IESerialize::write<IERenderable>(item.second->getFilePath(), &(*item.second));
                item.second->setIsEdited(false);
            }

            out << item.second->getFilePath()
                << item.second->getId()
                << item.second->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderableManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEResource::Type type;
        std::unique_ptr<IERenderable> renderable = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath >> type;

            if(type == IEResource::Type::Editor)
                continue;

            renderable = std::make_unique<IERenderable>();
            if(!IESerialize::read<IERenderable>(filePath, &(*renderable)))
                continue;

            manager.add(renderable->getId(), std::move(renderable));
        }

        return in;
    }
};

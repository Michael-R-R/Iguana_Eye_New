#pragma once

#include <QDataStream>

#include "IEResourceManager.h"
#include "IERenderable.h"
#include "IESerialize.h"
#include "IEFile.h"

class GameStartEvent;
class IEShader;

class IERenderableManager : public IEResourceManager<IERenderable>
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
        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            auto& renderable = *i.second;

            out << renderable.getType();

            if(renderable.getType() != IEResource::Type::Game)
                continue;

            if(renderable.getIsEdited())
            {
                if(!IEFile::doesPathExist(renderable.getFilePath()))
                    IEFile::makePath(renderable.getFilePath());

                if(IESerialize::write<IERenderable>(renderable.getFilePath(), &renderable))
                    renderable.setIsEdited(false);
            }

            out << renderable.getFilePath();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderableManager& manager)
    {
        int size = 0;
        in >> size;

        IEResource::Type type;
        QString filePath = "";

        for(int i = 0; i < size; i++)
        {
            in >> type;

            if(type != IEResource::Type::Game)
                continue;

            in >> filePath;

            auto renderable = std::make_unique<IERenderable>();
            if(!IESerialize::read<IERenderable>(filePath, &(*renderable)))
                continue;

            manager.add(renderable->getId(), std::move(renderable));
        }

        return in;
    }
};

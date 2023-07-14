#pragma once

#include <QVector>
#include <QHash>
#include <QPair>
#include <QString>
#include <any>

#include "IERenderable.h"
#include "IESerializeConverter.h"

struct IEInstRenderableNode
{
    QVector<QHash<QString, std::any>> hiddenData; // each index is an instance

    IEInstRenderableNode() :
        hiddenData()
    {

    }

    friend QDataStream& operator<<(QDataStream& out, const IEInstRenderableNode& node)
    {
        out << (int)node.hiddenData.size();
        foreach(auto& i, node.hiddenData)
        {
            out << (int)i.size();
            QHashIterator<QString, std::any> it(i);
            while(it.hasNext())
            {
                it.next();
                out << it.key();
                IESerializeConverter::write(out, it.value());
            }
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEInstRenderableNode& node)
    {
        int instCount = 0;
        in >> instCount;
        for(int i = 0; i < instCount; i++)
        {
            QHash<QString, std::any> values;

            int dataCount = 0;
            in >> dataCount;
            for(int j = 0; j < dataCount; j++)
            {
                QString name = "";
                std::any val;

                in >> name;
                IESerializeConverter::read(in, val);

                values.insert(name, val);
            }

            node.hiddenData.append(values);
        }

        return in;
    }
};

class IEInstRenderable : public IERenderable
{
protected:
    QVector<IEInstRenderableNode*> instNodes;
    int shown;
    int hidden;

public:
    IEInstRenderable(IERenderableType ieType, QObject* parent = nullptr);
    IEInstRenderable(IERenderableType ieType, const QString& path, QObject* parent = nullptr);
    IEInstRenderable(IERenderable* parent);
    IEInstRenderable(const IEInstRenderable&) = delete;
    virtual ~IEInstRenderable();

    bool operator==(const IEInstRenderable& other) { return IERenderable::operator==(other); }
    bool operator!=(const IEInstRenderable& other) { return IERenderable::operator!=(other); }
    bool operator<(const IEInstRenderable& other) { return IERenderable::operator<(other); }
    bool operator>(const IEInstRenderable& other) { return IERenderable::operator>(other); }

protected:
    virtual bool handleBuild(const int index) override = 0;
    virtual bool handleBuildRelease(const int index) override = 0;
    virtual void handleDraw(const int index, const QVector<std::any>& args) override = 0;

public:
    virtual int appendNode(IERenderableNode* node) override;
    virtual bool removeNode(const int index) override;
    virtual void cleanup() override;

    IEInstRenderableNode* getInstNode(const int index);

    int addShown();
    int addShownFromHidden(const int index);
    bool removeShown(const int index);

    int addHiddenFromShown(const int index);
    bool removeHidden(const int index);

    QHash<QString, std::any> getInstValues(const int index, const int shownIndex);
    QVector<IEInstRenderableNode*>& getInstNodes() { return instNodes; }
    int shownCount() const { return shown; }
    int hiddenCount() const { return hidden; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

protected:
    bool shownIndexBoundsCheck(const int index);
    bool hiddenIndexBoundsCheck(const int index);

private:
    bool indexBoundsCheck(const int index);
};


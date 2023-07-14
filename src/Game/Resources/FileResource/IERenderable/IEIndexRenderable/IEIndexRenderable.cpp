#include "IEIndexRenderable.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEIndexRenderable::IEIndexRenderable(QObject* parent) :
    IERenderable(IERenderableType::Index, parent),
    indexNodes()
{

}

IEIndexRenderable::IEIndexRenderable(const QString& path, QObject* parent) :
    IERenderable(IERenderableType::Index, path, parent),
    indexNodes()
{

}

IEIndexRenderable::IEIndexRenderable(IERenderable* parent) :
    IERenderable(parent),
    indexNodes()
{

}

IEIndexRenderable::~IEIndexRenderable()
{
    IEIndexRenderable::cleanup();
}

bool IEIndexRenderable::handleBuild(const int index)
{
    if(index < 0 || index >= indexNodes.size())
        return false;

    indexNodes[index]->IBO->build();

    return true;
}

bool IEIndexRenderable::handleBuildRelease(const int index)
{
    if(index < 0 || index >= indexNodes.size())
        return false;

    indexNodes[index]->IBO->release();

    return true;
}

void IEIndexRenderable::handleDraw(const int index, const QVector<std::any>&)
{
    if(index < 0 || index >= nodes.size())
        return;

    IERenderableNode* rNode = nodes[index];
    IEIndexRenderableNode* iNode = indexNodes[index];

    rNode->VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElements(rNode->primitiveMode,
                       iNode->IBO->count(),
                       GL_UNSIGNED_INT,
                       0);
}

int IEIndexRenderable::appendNode(IERenderableNode* node)
{
    const int index = IERenderable::appendNode(node);
    if(index < 0) { return -1; }

    indexNodes.append(new IEIndexRenderableNode());

    return index;
}

bool IEIndexRenderable::removeNode(const int index)
{
    if(!IERenderable::removeNode(index))
        return false;

    auto* temp = indexNodes[index];
    indexNodes.removeAt(index);
    delete temp;

    return true;
}

void IEIndexRenderable::cleanup()
{
    IERenderable::cleanup();

    foreach (auto* i, indexNodes)
    {
        delete i;
    }

    indexNodes.clear();
}

IEIndexRenderableNode* IEIndexRenderable::getIndexNode(const int index)
{
    if(index < 0 || index >= indexNodes.size())
        return nullptr;

    return indexNodes[index];
}

QDataStream& IEIndexRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IERenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEIndexRenderable&>(obj);

    out << (int)renderable.indexNodes.size();
    foreach(auto* i, renderable.indexNodes)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEIndexRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IERenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEIndexRenderable&>(obj);

    int nodeCount = 0;
    in >> nodeCount;
    for(int i = 0; i < nodeCount; i++)
    {
        auto* node = new IEIndexRenderableNode();
        in >> *node;

        renderable.indexNodes.append(node);
    }

    return in;
}

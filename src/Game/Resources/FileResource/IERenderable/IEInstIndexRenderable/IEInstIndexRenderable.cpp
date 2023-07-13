#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstIndexRenderable::IEInstIndexRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, parent),
    instIndexNodes()
{

}

IEInstIndexRenderable::IEInstIndexRenderable(const QString& path, QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, path, parent),
    instIndexNodes()
{

}

IEInstIndexRenderable::IEInstIndexRenderable(IERenderable* parent) :
    IEInstRenderable(parent),
    instIndexNodes()
{

}

IEInstIndexRenderable::~IEInstIndexRenderable()
{
    cleanup();
}

bool IEInstIndexRenderable::handleBuild(const int index)
{
    if(index < 0 || index >= instIndexNodes.size())
        return false;

    instIndexNodes[index]->IBO->build();

    return true;
}

bool IEInstIndexRenderable::handleBuildRelease(const int index)
{
    if(index < 0 || index >= instIndexNodes.size())
        return false;

    instIndexNodes[index]->IBO->release();

    return true;
}

void IEInstIndexRenderable::handleDraw(const int index, const QVector<std::any>&)
{
    if(index < 0 || index >= nodes.size())
        return;

    if(shown < 0)
        return;

    IERenderableNode* rNode = nodes[index];
    IEInstIndexRenderableNode* iiNode = instIndexNodes[index];

    rNode->VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElementsInstanced(rNode->primitiveMode,
                                iiNode->IBO->count(),
                                GL_UNSIGNED_INT,
                                0,
                                shown);
}

int IEInstIndexRenderable::appendNode(IERenderableNode* node)
{
    const int index = IEInstRenderable::appendNode(node);
    if(index < 0) { return -1; }

    instIndexNodes.append(new IEInstIndexRenderableNode());

    return index;
}

bool IEInstIndexRenderable::removeNode(const int index)
{
    if(IEInstRenderable::removeNode(index))
        return false;

    auto* temp = instIndexNodes[index];
    instIndexNodes.removeAt(index);
    delete temp;

    return true;
}

void IEInstIndexRenderable::cleanup()
{
    IEInstRenderable::cleanup();

    foreach (auto* i, instIndexNodes)
    {
        delete i;
        i = nullptr;
    }

    instIndexNodes.clear();
}

IEInstIndexRenderableNode* IEInstIndexRenderable::getInstIndexNode(const int index)
{
    if(index < 0 || index >= instIndexNodes.size())
        return nullptr;

    return instIndexNodes[index];
}

QDataStream& IEInstIndexRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEInstRenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstIndexRenderable&>(obj);

    // TODO implement

    return out;
}

QDataStream& IEInstIndexRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IEInstRenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstIndexRenderable&>(obj);

    // TODO implement

    return in;
}

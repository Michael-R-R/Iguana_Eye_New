#include "IERenderableImport.h"
#include "IEMesh.h"
#include "IERenderable.h"
#include "IEFile.h"
#include "IEBufferObjectFactory.h"

bool IERenderableImport::importPath(const QString& path,
                                    IERenderable& renderable,
                                    IEMesh& mesh,
                                    const uint64_t maID,
                                    const uint64_t sID)
{
    renderable.updateId(convertRenderablePath(path));

    renderable.setMeshID(mesh.getID());
    renderable.setMaterialID(maID);
    renderable.setShaderID(sID);

     foreach(auto* meNode, mesh.getNodes())
    {
        auto* rNode = new IERenderableNode();

        processRenderableNode(meNode, rNode, &renderable);

        renderable.appendNode(rNode);
    }

     return true;
}

QString IERenderableImport::convertRenderablePath(const QString& path)
{
    QString newPath = path;
    QString oldExt = IEFile::extractExtension(path);

    return newPath.replace(oldExt, ".ierend");
}

void IERenderableImport::processRenderableNode(IEMeshNode* meNode, IERenderableNode* rNode, QObject* parent)
{
    rNode->buffers.insert("aPos", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, parent));
    rNode->buffers.insert("aNormal", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, parent));
    rNode->buffers.insert("aTangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, parent));
    rNode->buffers.insert("aBitangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, parent));
    rNode->buffers.insert("aTexCoord", IEBufferObjectFactory::make(IEBufferType::Vec2, 0, 0, 0, parent));

    rNode->buffers["aPos"]->setValues(meNode->positions);
    rNode->buffers["aNormal"]->setValues(meNode->normals);
    rNode->buffers["aTangent"]->setValues(meNode->tangents);
    rNode->buffers["aBitangent"]->setValues(meNode->bitangents);
    rNode->buffers["aTexCoord"]->setValues(meNode->textures);
}

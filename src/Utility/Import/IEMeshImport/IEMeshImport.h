#pragma once

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IEEnum.h"

class QObject;
class IEResource;
class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IETexture2DManager;
struct IEMeshNode;
struct IEMaterialNode;
struct IERenderableNode;

class IEMeshImport
{
public:
    static bool importPath(const QString& path, IEMesh& me);
    static bool importPath(const QString& path, IEMesh& me, IEMaterial& ma);
    static bool importPath(const QString& path, IEMesh& me, IEMaterial& ma, IEShader& s, IERenderable& r);
    static QString convertMeshPath(const QString& path);
    static QString convertMaterialPath(const QString& path);
    static QString convertRenderablePath(const QString& path);

private:
    static void replaceExtension(QString path, const QString extension, IEResource& resource);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* me);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* me, IEMaterial* ma);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* me, IEMaterial* ma, IERenderable* r);
    static void processMeshNode(aiMesh* assimpMesh, IEMeshNode* meNode);
    static void processMaterialNode(aiMesh* assimpMesh, const aiScene* scene, const QString& filePath, IEMaterialNode* maNode);
    static void processRenderableNode(IEMeshNode* meNode, IERenderableNode* rNode, QObject* parent);

    static void load2DTextures(const QString& relPath,
                               aiMaterial* assimpMat,
                               aiTextureType assimpTexType,
                               IETextureType ieTexType,
                               IEMaterialNode* maNode,
                               IETexture2DManager* manager);
};


#pragma once

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IEEnum.h"

class IEResource;
class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IETexture2DManager;

class IEMeshImport
{
public:
    static bool importMesh(const QString& path, IEMesh& mesh);
    static bool importMesh(const QString& path, IEMesh& mesh, IEMaterial& material);
    static bool importMesh(const QString& path, IEMesh& mesh, IEMaterial& material, IEShader& shader, IERenderable& renderable);

private:
    static void replaceExtension(QString path, const QString extension, IEResource& resource);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* meParent);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* meParent, IEMaterial* maParent);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* meParent, IEMaterial* maParent, IERenderable* rParent);
    static void processMesh(aiMesh* assimpMesh, IEMesh* ieMesh);
    static void processMaterial(aiMesh* assimpMesh, const aiScene* scene, IEMaterial* ieMaterial);
    static void processRenderable(IEMesh* mesh, IERenderable* renderable);

    static void load2DTextures(const QString& relPath,
                               aiMaterial* assimpMat,
                               aiTextureType assimpTexType,
                               IETextureType ieTexType,
                               IEMaterial* ieMaterial,
                               IETexture2DManager* manager);
};


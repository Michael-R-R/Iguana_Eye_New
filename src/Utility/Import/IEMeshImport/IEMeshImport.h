#pragma once

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class IEMesh;
class IEMaterial;

class IEMeshImport
{

public:
    static bool importMesh(const QString& path, IEMesh& mesh);
    static bool importMesh(const QString &path, IEMesh &mesh, IEMaterial& material);

private:
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* ieMesh);
    static void processNode(aiNode* node, const aiScene* scene, IEMesh* ieMesh, IEMaterial* ieMaterial);
    static void processMesh(aiMesh* assimpMesh, IEMesh* ieMesh);
    static void processMaterial(aiMesh* assimpMesh, const aiScene* scene, IEMaterial* ieMaterial);
};


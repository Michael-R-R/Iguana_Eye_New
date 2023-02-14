#pragma once

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class IEMesh;

class IEObjLoader
{

public:
    static IEMesh* loadMesh(const QString& path);

private:
    static IEMesh* processNode(aiNode* node, const aiScene* scene, IEMesh* mesh);
    static IEMesh* processMesh(aiMesh* assimpMesh, const aiScene* scene, IEMesh* ieMesh);
};


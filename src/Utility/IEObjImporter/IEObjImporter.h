#pragma once

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class IEMesh;

class IEObjImporter
{

public:
    static bool importMesh(const QString &path, IEMesh& mesh);

private:
    static void processNode(aiNode* node, const aiScene* scene, IEMesh& mesh);
    static void processMesh(aiMesh* assimpMesh, const aiScene* scene, IEMesh& ieMesh);
};


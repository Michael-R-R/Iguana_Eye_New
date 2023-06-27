#pragma once

#include <QString>

class IEMesh;

class IEMeshExport
{

public:
    static void exportMesh(const QString& path, IEMesh* mesh);
};


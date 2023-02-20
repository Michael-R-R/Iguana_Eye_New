#pragma once

#include <QString>

class IEMesh;

class IEObjExporter
{

public:
    static void exportMesh(const QString& path, IEMesh* mesh);
};


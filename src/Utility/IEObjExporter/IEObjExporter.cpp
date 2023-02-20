#include "IEObjExporter.h"
#include "IEFile.h"
#include "IEMesh.h"

void IEObjExporter::exportMesh(const QString& path, IEMesh* mesh)
{
    QString content = "# Iguana Eye OBJ File\n";

    QString x = "";
    QString y = "";
    QString z = "";

    auto posVerts = mesh->getPosVertices();
    for(QVector3D item : posVerts)
    {
        x = QString::number(item.x(), 'f', 6);
        y = QString::number(item.y(), 'f', 6);
        z = QString::number(item.z(), 'f', 6);
        content.append(QString("v %1 %2 %3\n").arg(x, y, z));
    }

    auto texVerts = mesh->getTexVertices();
    for(QVector2D item : texVerts)
    {
        x = QString::number(item.x(), 'f', 6);
        y = QString::number(item.y(), 'f', 6);
        content.append(QString("vt %1 %2\n").arg(x, y));
    }

    auto normVerts = mesh->getNormVertices();
    for(QVector3D item : normVerts)
    {
        x = QString::number(item.x(), 'f', 6);
        y = QString::number(item.y(), 'f', 6);
        z = QString::number(item.z(), 'f', 6);
        content.append(QString("vn %1 %2 %3\n").arg(x, y, z));
    }

    // Smooth polygon shading off
    content.append("s off\n");

    auto indices = mesh->getIndices();
    for(int i = 0; i < indices.size(); i+=3)
    {
        x = QString::number(indices[i + 0]);
        y = QString::number(indices[i + 1]);
        z = QString::number(indices[i + 2]);
        content.append(QString("f %1/%2/%3\n").arg(x, y, z));
    }

    IEFile::write(path, content);
}

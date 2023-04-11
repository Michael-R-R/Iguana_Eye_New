#include "IEDefaultMaterial.h"

IEDefaultMaterial::IEDefaultMaterial(const QString& path) :
    IEMaterial(path)
{
    objectColor = QColor(30, 30, 30, 255);
    uniformData.add("uColor", QColor(0, 0, 255, 255));
    isViewable = false;
}

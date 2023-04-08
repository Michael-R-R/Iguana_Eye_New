#include "IEDefaultMaterial.h"

IEDefaultMaterial::IEDefaultMaterial(const QString& path) :
    IEMaterial(path)
{
    objectColor = QColor(30, 30, 30, 255);
}

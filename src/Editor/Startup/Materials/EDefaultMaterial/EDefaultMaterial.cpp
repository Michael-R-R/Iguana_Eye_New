#include "EDefaultMaterial.h"

EDefaultMaterial::EDefaultMaterial(const QString& path) :
    IEMaterial(path)
{
    objectColor = QColor(30, 30, 30, 255);
}

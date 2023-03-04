#include "EDefaultMaterial.h"

EDefaultMaterial::EDefaultMaterial(const QString& path, const unsigned long long id) :
    IEMaterial("", id)
{
    objectColor = QColor(30, 30, 30, 255);
}

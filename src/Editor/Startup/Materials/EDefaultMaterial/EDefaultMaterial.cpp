#include "EDefaultMaterial.h"

EDefaultMaterial::EDefaultMaterial(const QString& path, const unsigned long long id) :
    IEMaterial(path, id)
{
    this->setType(Type::Editor);

    objectColor = QColor(30, 30, 30, 255);
}

#include "EDefaultMaterial.h"

EDefaultMaterial::EDefaultMaterial(const unsigned long long id) :
    IEMaterial(id)
{

}

void EDefaultMaterial::setup()
{
    objectColor = QColor(30, 30, 30, 255);
}

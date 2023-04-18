#include "IEDefaultMaterial.h"

IEDefaultMaterial::IEDefaultMaterial(const QString& path, QObject* parent) :
    IEMaterial(path, parent)
{
    objectColor = QColor(30, 30, 30, 255);
    uniformData.add("uColor", QColor(0, 0, 255, 255));
}

IEDefaultMaterial::~IEDefaultMaterial()
{

}

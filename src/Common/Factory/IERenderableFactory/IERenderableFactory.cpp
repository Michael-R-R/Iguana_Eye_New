#include "IERenderableFactory.h"
#include "IEInstIndexRenderable.h"
#include <QObject>

IERenderable* IERenderableFactory::make(const IERenderableType type, QObject* parent)
{
    switch(type)
    {
    case IERenderableType::Index: { return nullptr; }
    case IERenderableType::I_Index: { return new IEInstIndexRenderable(parent); }
    case IERenderableType::Vertex: { return nullptr; }
    case IERenderableType::I_Vertex: { return nullptr; }
    case IERenderableType::Unknown: { return nullptr; }
    default:  { return nullptr; }
    }
}

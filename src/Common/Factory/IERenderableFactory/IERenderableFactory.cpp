#include "IERenderableFactory.h"
#include "IEIndexRenderable.h"
#include "IEInstIndexRenderable.h"
#include "IEVertRenderable.h"
#include "IEInstVertRenderable.h"
#include <QObject>

IERenderable* IERenderableFactory::make(const IERenderableType type, QObject* parent)
{
    switch(type)
    {
    case IERenderableType::Index: { return new IEIndexRenderable(parent); }
    case IERenderableType::I_Index: { return new IEInstIndexRenderable(parent); }
    case IERenderableType::Vertex: { return new IEVertRenderable(parent); }
    case IERenderableType::I_Vertex: { return new IEInstVertRenderable(parent); }
    case IERenderableType::Unknown: { return nullptr; }
    default:  { return nullptr; }
    }
}

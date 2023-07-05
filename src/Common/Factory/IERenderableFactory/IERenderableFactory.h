#pragma once

#include "IEEnum.h"

class IERenderable;
class QObject;

class IERenderableFactory
{
public:
    static IERenderable* make(const IERenderableType type, QObject* parent = nullptr);
};


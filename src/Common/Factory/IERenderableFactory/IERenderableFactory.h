#pragma once

#include "IEEnum.h"

class IERenderable;

class IERenderableFactory
{
public:
    static IERenderable* make(const IERenderableType type);
};


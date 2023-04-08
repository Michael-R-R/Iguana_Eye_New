#pragma once

#include "IEShader.h"

class IEDefaultShader : public IEShader
{
public:
    IEDefaultShader(const QString& path);
    ~IEDefaultShader();
};


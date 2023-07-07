#pragma once

#include "IEEnum.h"

class QObject;
class IEBufferObject;

class IEBufferObjectFactory
{
public:
    static IEBufferObject* make(const IEBufferType type, QObject* parent = nullptr);
    static IEBufferObject* make(const IEBufferType type,
                                const int stride,
                                const int offset,
                                const int divisor,
                                QObject *parent = nullptr);
};


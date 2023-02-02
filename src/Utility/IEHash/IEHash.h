#pragma once

#include <QString>

class IEHash
{

public:
    static unsigned long long Compute(const QString& str);
};


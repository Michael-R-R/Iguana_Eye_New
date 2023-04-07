#include "IEResource.h"

IEResource::IEResource(const QString& path, const unsigned long long resourceId) :
    filePath(path),
    id(resourceId)
{

}

IEResource::~IEResource()
{

}

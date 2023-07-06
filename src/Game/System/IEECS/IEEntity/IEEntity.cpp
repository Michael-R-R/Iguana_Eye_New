#include "IEEntity.h"

IEEntity::IEEntity() :
    id(-1)
{

}

IEEntity::IEEntity(const int id_) :
    id(id_)
{

}

IEEntity::IEEntity(const IEEntity& other) :
    id(other.id)
{

}

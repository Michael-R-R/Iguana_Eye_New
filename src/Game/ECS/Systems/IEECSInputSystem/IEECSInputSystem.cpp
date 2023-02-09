#include "IEECSInputSystem.h"

IEECSInputSystem::IEECSInputSystem() :
    IEECSSystem()
{

}

IEECSInputSystem::~IEECSInputSystem()
{

}

int IEECSInputSystem::attach(const IEEntity entity)
{
    return -1;
}

bool IEECSInputSystem::detach(const IEEntity entity)
{
    return false;
}

void IEECSInputSystem::onUpdateFrame()
{

}

void IEECSInputSystem::onPostUpdateFrame()
{

}

void IEECSInputSystem::onRenderFrame()
{

}

QDataStream& operator<<(QDataStream& out, const IEECSInputSystem& system)
{
    out << system.getEntityMap();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEECSInputSystem& system)
{
    QMap<IEEntity, int> entityMap;

    in >> entityMap;

    system.setEntityMap(entityMap);

    return in;
}

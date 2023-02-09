#pragma once

#include <QDataStream>

#include "IEECSSystem.h"

class IEECSInputSystem : public IEECSSystem
{

public:
    IEECSInputSystem();
    ~IEECSInputSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame() override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;
};

QDataStream& operator<<(QDataStream& out, const IEECSInputSystem& system);
QDataStream& operator>>(QDataStream& in, IEECSInputSystem& system);

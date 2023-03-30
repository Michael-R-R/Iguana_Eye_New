#pragma once

#include <memory>
#include <QVector2D>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IETime;
class IEInput;
class IERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime& time;
    IEInput& input;
    IERenderEngine& renderEngine;
    std::unique_ptr<ECamera> camera;

public:
    IEGameStopState(IEGame& game);
    ~IEGameStopState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;
};


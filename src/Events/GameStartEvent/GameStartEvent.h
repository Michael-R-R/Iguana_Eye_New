#pragma once

class IEGame;
class IETime;
class IEInput;
class IEScriptEngine;
class IEPhysicsEngine;
class IERenderEngine;
class IEScene;

class GameStartEvent
{
    // Does not own these pointers
    IEGame* game;

public:
    GameStartEvent(IEGame* game_);
    ~GameStartEvent();

    IEGame& getGame() const;
    IETime& getTime() const;
    IEInput& getInput() const;
    IEScriptEngine& getScriptEngine() const;
    IEPhysicsEngine& getPhysicsEngine() const;
    IERenderEngine& getRenderEngine() const;
    IEScene& getScene() const;
};


#pragma once

class AppStartEvent;

class ESceneStartup
{

public:
    static void startup(const AppStartEvent& event);

private:
    static void buildGridRenderable(const AppStartEvent& event);
};


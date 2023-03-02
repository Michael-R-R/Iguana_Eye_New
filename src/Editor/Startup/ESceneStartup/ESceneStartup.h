#pragma once

class AppStartEvent;

class ESceneStartup
{

public:
    static void startup(const AppStartEvent& event);

private:
    static void addDefaultCamera(const AppStartEvent& event);
    static void addDefaultMaterial(const AppStartEvent& event);
    static void addDefaultShader(const AppStartEvent& event);
    static void buildGridRenderable(const AppStartEvent& event);
};


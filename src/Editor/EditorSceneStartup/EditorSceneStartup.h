#pragma once

class AppStartEvent;

class EditorSceneStartup
{

public:
    static void startup(const AppStartEvent& event);

private:
    static void buildDefaultMeshes(const AppStartEvent& event);
    static void buildDefaultMaterials(const AppStartEvent& event);
    static void buildDefaultShaders(const AppStartEvent& event);

    static void buildGridRenderable(const AppStartEvent& event);
};


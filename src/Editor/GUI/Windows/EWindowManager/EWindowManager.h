#pragma once

#include <map>
#include <memory>

#include "EWindow.h"

class AppStartEvent;

class EWindowManager
{
    std::map<QString, std::unique_ptr<EWindow>> windowCollection;

public:
    EWindowManager();
    ~EWindowManager();

    void startup(const AppStartEvent& event);

    void showAll();
    void hideAll();

    bool appendWindow(const QString& key, std::unique_ptr<EWindow> value);
    bool removeWindow(const QString& key);
    EWindow* getValue(const QString& key);
    bool doesExist(const QString& key) const;

    void clear();

private:
    void setupOptionsWindow(const AppStartEvent& event);
    void setupGlslEditorWindow(const AppStartEvent& event);
    void setupFileExplorerWindow(const AppStartEvent& event);
};


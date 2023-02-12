#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class SaveGameFileAction : public MenuAction
{

public:
    SaveGameFileAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent = nullptr);
    ~SaveGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


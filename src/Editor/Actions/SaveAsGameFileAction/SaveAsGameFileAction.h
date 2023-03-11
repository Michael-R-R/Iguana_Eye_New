#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class SaveAsGameFileAction : public MenuAction
{

public:
    SaveAsGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveAsGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


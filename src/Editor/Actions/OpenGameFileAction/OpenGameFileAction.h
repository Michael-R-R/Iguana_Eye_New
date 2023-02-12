#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class OpenGameFileAction : public MenuAction
{

public:
    OpenGameFileAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent = nullptr);
    ~OpenGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void tryOpenPath(const QString path, ApplicationWindow* window);
};


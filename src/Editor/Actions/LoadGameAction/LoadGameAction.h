#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class LoadGameAction : public MenuAction
{

public:
    LoadGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent = nullptr);
    ~LoadGameAction();

private:
    QString askForPath(QWidget* parent);
    void tryOpenPath(const QString path, ApplicationWindow* window);
};


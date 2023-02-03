#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class SaveGameAction : public MenuAction
{

public:
    SaveGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent = nullptr);
    ~SaveGameAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


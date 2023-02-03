#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class SaveAsGameAction : public MenuAction
{

public:
    SaveAsGameAction(ApplicationWindow* window, InputKey* shortcut, QObject* parent = nullptr);
    ~SaveAsGameAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


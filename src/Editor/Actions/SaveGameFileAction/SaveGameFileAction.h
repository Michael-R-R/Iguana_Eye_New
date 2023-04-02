#pragma once

#include "BaseAction.h"

class ApplicationWindow;

class SaveGameFileAction : public BaseAction
{

public:
    SaveGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


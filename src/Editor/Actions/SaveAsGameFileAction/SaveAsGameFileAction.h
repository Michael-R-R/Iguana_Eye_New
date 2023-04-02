#pragma once

#include "BaseAction.h"

class ApplicationWindow;

class SaveAsGameFileAction : public BaseAction
{

public:
    SaveAsGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveAsGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void trySavePath(const QString path, ApplicationWindow* window);
};


#pragma once

#include "BaseAction.h"

class ApplicationWindow;

class OpenGameFileAction : public BaseAction
{

public:
    OpenGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~OpenGameFileAction();

private:
    QString askForPath(QWidget* parent);
    void tryOpenPath(const QString path, ApplicationWindow* window);
};


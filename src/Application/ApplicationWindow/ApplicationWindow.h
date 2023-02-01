#pragma once

#include <QMainWindow>

#include "PreprocessDirectives.h"

class Game;
class Editor;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ApplicationWindow *ui;

    Game* game;
    Editor* editor;

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void shutdown();

private slots:
    void startup();
};

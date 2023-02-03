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

    const QString applicationTitle;
    QString windowTitle;
    QString savePath;

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void addTextToTitle(const QString text);
    void displayApplicationModified(const bool isModified);
    void shutdown();

    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }

private slots:
    void startup();

public slots:
    bool saveToFile(const QString& path);
    bool loadFromFile(const QString& path);
};

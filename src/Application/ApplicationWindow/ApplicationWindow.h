#pragma once

#include <QMainWindow>

#include "PreprocessDirectives.h"

class IEGame;
class Editor;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ApplicationWindow *ui;

    IEGame* game;
    Editor* editor;

    const QString applicationTitle;
    QString windowTitle;
    QString savePath;

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void addTextToTitle(const QString text);
    void setModifiedStatus(const bool isModified);

    void shutdown();

private slots:
    void startup();

private:
    void setupGame();
    void setupEditor();
    void clearActions();

public slots:
    void newFile();
    bool saveToFile(const QString& path);
    bool openFromFile(const QString& path);

public:
    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }
};

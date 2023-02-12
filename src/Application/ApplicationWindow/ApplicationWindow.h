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
    void modifiedStatus(const bool isModified);
    void shutdown();

    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }

private slots:
    void startup();

public slots:
    void newFile();
    bool saveToFile(const QString& path);
    bool loadFromFile(const QString& path);
};

#pragma once

#include <QMainWindow>
#include <memory>

#include "PreprocessDirectives.h"

class IEGame;
class Editor;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ApplicationWindow* ui;

    std::unique_ptr<IEGame> game;
    std::unique_ptr<Editor> editor;

    const QString permenentTitle;
    QString tempTitle;
    QString savePath;

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void startup();
    void shutdown();

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);

private:
    void initalize();
    void clearActions();
    void deserialize(const QString& path);

public slots:
    void newFile();
    bool saveToFile(const QString& path);
    bool openFromFile(const QString& path);

public:
    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }
};

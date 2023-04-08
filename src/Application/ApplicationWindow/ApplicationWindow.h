#pragma once

#include <QMainWindow>
#include <QSharedPointer>

class IEGame;
class Editor;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

    Ui::ApplicationWindow* ui;

    QSharedPointer<IEGame> game;
    QSharedPointer<Editor> editor;

    const QString permenentTitle;
    QString tempTitle;
    QString savePath;

    bool doBuildEditor;

public:
    ApplicationWindow(bool buildEditor, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void startup();
    void shutdown();

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);

    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }

private:
    void initalize();
    void clearActions();

public slots:
    void newFile();
    bool saveToFile(const QString& path);
    bool openFromFile(const QString& path);
};

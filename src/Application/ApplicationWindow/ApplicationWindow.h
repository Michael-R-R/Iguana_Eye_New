#pragma once

#include <QMainWindow>

#include "Serializable.h"
#include "ApplicationFileHandler.h"

class IEGame;
class Editor;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow, public Serializable
{
    Q_OBJECT

    ApplicationWindow();

    Ui::ApplicationWindow* ui;

    ApplicationFileHandler appFileHandler;

    IEGame* game;
    Editor* editor;

    const QString permenentTitle;
    QString tempTitle;

public:
    static ApplicationWindow& instance();
    ApplicationWindow(const ApplicationWindow&) = delete;
    void operator=(const ApplicationWindow&) = delete;
    ~ApplicationWindow();

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);

    void init();
    void startUp();
    void shutdown();
    void onSerialize() const;
    void onDeserialize() const;

    void newFile();
    void saveFile();
    void saveAsFile(const QString& path);
    void openFile(const QString& path);

    IEGame* getGame() const { return game; }
    Editor* getEditor() const { return editor; }

private:
    void clearActions();

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

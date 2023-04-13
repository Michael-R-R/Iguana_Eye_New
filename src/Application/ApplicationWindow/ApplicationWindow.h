#pragma once

#include <QMainWindow>
#include <QSharedPointer>

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

    QSharedPointer<IEGame> game;
    QSharedPointer<Editor> editor;

    const QString permenentTitle;
    QString tempTitle;

public:
    static ApplicationWindow& instance();
    ApplicationWindow(const ApplicationWindow&) = delete;
    void operator=(const ApplicationWindow&) = delete;
    ~ApplicationWindow();

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);

    void startup();
    void initalize();
    void shutdown();

    void newFile();
    void saveToFile();
    void saveAsToFile(const QString& path);
    void openFromFile(const QString& path);

    IEGame* getGame() const { return &(*game); }
    Editor* getEditor() const { return &(*editor); }

private:
    void clearActions();

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

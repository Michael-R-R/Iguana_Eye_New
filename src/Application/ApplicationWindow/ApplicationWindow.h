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

    Ui::ApplicationWindow* ui;

    ApplicationFileHandler appFileHandler;

    QSharedPointer<IEGame> game;
    QSharedPointer<Editor> editor;

    const QString permenentTitle;
    QString tempTitle;

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

public slots:
    void newFile();
    void saveToFile();
    void saveAsToFile(const QString& path);
    void openFromFile(const QString& path);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QToolButton>
#include <QMap>

class EWCollapsingHeader : public QWidget
{
    Q_OBJECT

    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;

    QFrame* headerFrame;
    QToolButton* headerButton;

    bool isOpen;

    QMap<QString, QWidget*> widgetCollection;

public:
    EWCollapsingHeader(QString title, QWidget* parent = nullptr);
    ~EWCollapsingHeader();

    bool appendWidget(const QString title, QWidget* widget);
    bool removeWidget(const QString& title);
    bool doesExist(const QString& title);

    QWidget* getWidget(const QString& title);

private:
    void setupHeaderFrame();
    void setupHeaderButton(const QString& title);

signals:
    void headerOpened();
    void headerClosed();
};


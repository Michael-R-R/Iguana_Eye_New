#pragma once

#include <QDockWidget>

class Window : public QDockWidget
{
    Q_OBJECT

    bool isActive;

public:
    Window(QString title, QWidget* parent = nullptr);
    ~Window();

    void toggleVisibilty(bool status);
    void setStyleByString(const QString& style);
    void setStyleByFile(const QString& path);

    bool getIsActive() { return isActive; }

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};


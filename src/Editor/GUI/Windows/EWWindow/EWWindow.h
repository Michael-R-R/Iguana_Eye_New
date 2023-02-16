#pragma once

#include <QDockWidget>

class EWWindow : public QDockWidget
{
    Q_OBJECT

    bool isActive;

public:
    EWWindow(QString title, QWidget* parent = nullptr);
    ~EWWindow();

    void toggleVisibilty(bool status);
    void setStyleByString(const QString& style);
    void setStyleByFile(const QString& path);

    bool getIsActive() { return isActive; }

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};


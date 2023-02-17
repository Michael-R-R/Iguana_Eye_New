#pragma once

#include <QDockWidget>

class EWindow : public QDockWidget
{
    Q_OBJECT

    bool isActive;

public:
    EWindow(QString title, QWidget* parent = nullptr);
    ~EWindow();

    void toggleVisibilty(bool status);
    void setStyleByString(const QString& style);
    void setStyleByFile(const QString& path);

    bool getIsActive() { return isActive; }

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};


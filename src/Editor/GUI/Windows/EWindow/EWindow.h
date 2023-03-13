#pragma once

#include <QDockWidget>

class EWindow : public QDockWidget
{
    Q_OBJECT

    const QString permenentTitle;
    QString tempTitle;
    bool hasModifications;
    bool isActive;

public:
    EWindow(const QString& title, QWidget* parent = nullptr);
    ~EWindow();

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);
    void toggleVisibilty(bool status);
    void setStyleByString(const QString& style);
    void setStyleByFile(const QString& path);

    bool getHasModifications() { return hasModifications; }
    bool getIsActive() { return isActive; }

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};


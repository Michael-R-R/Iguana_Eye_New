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
    EWindow(QString title, QWidget* parent = nullptr);
    ~EWindow();

    virtual void startup() = 0;

    void modifyTitle(const QString& text);
    void setModified(const bool isModified);
    void toggleVisibilty(bool status);
    void setStyleByString(const QString& style);
    void setStyleByFile(const QString& path);

    const QString& getPermTitle() const { return permenentTitle; }
    bool getHasModifications() const { return hasModifications; }
    bool getIsActive() const { return isActive; }

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};


#pragma once

#include <QPushButton>

class EWDirectoryButton : public QPushButton
{
    Q_OBJECT

    QString dirName;
    QString dirPath;
    int index;

public:
    EWDirectoryButton(const QString& name, const QString& path,
                      const int indexInList, QWidget* parent = nullptr);
    ~EWDirectoryButton() {}

    QString getDirName() const { return dirName; }
    QString getDirPath() const { return dirPath; }
    int getIndex() const { return index; }

private slots:
    void emitIndex();

signals:
    void historyButtonClicked(const int index);
};


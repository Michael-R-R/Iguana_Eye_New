#pragma once

#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>

class BaseInput;
class InputKey;

class EWHotkeyTable : public QTabWidget
{
    QVBoxLayout* vLayout;

public:
    EWHotkeyTable(QWidget* parent = nullptr);
    ~EWHotkeyTable();

protected:
    void addTable(QString title, QTableWidget* table);
    QTableWidget* createTable(const BaseInput* input, const QMap<QString, InputKey*>& keys);

private:
    void fillInTable(QTableWidget* table, const BaseInput* input, const QMap<QString, InputKey*>& keys);
    void setupButtonConnect(QPushButton* button, const BaseInput* input, InputKey* key);
    QString convertText(QString text, int key);
};


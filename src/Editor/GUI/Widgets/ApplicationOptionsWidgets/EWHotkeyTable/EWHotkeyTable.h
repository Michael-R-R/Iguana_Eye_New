#pragma once

#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>

#include "InputContainer.h"

class EWHotkeyTable : public QTabWidget
{
    QVBoxLayout* vLayout;

public:
    EWHotkeyTable(QWidget* parent = nullptr);
    ~EWHotkeyTable();

protected:
    void addTable(QString title, QTableWidget* table);
    QTableWidget* createTable(const InputContainer& inputContainer, const QMap<QString, InputKey*>& keys);

private:
    void fillInTable(QTableWidget* table, const InputContainer& inputContainer, const QMap<QString, InputKey*>& keys);
    void setupButtonConnect(QPushButton* button, const InputContainer& inputContainer, InputKey* key);
    QString convertText(QString text, int key);
};


#include "EWHotkeyTable.h"
#include "EWFetchUserInput.h"
#include "BaseInput.h"
#include "InputKey.h"

EWHotkeyTable::EWHotkeyTable(QWidget* parent) :
    QTabWidget(parent),
    vLayout(new QVBoxLayout(this))
{

}

EWHotkeyTable::~EWHotkeyTable()
{

}

void EWHotkeyTable::addTable(QString title, QTableWidget* table)
{
    this->addTab(table, title);
}

QTableWidget* EWHotkeyTable::createTable(const BaseInput* input, const QMap<QString, InputKey*>& keys)
{
    int rows = keys.size();
    int cols = 2;

    auto table = new QTableWidget(rows, cols, this);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    this->fillInTable(table, input, keys);

    return table;
}

void EWHotkeyTable::fillInTable(QTableWidget* table, const BaseInput* input, const QMap<QString, InputKey*>& keys)
{
    int row = 0;

    QMapIterator<QString, InputKey*> it(keys);
    while(it.hasNext())
    {
        it.next();

        auto nameLabel = new QLabel(it.key(), table);

        int key = it.value()->getKey();
        QString keySequenceText = it.value()->getKeySequence().toString();
        QString buttonTitle = convertText(keySequenceText, key);
        auto button = new QPushButton(buttonTitle, table);
        button->setFlat(true);
        setupButtonConnect(button, input, it.value());

        table->setCellWidget(row, 0, nameLabel);
        table->setCellWidget(row, 1, button);

        row++;
    }
}

void EWHotkeyTable::setupButtonConnect(QPushButton* button, const BaseInput* input, InputKey* key)
{
    connect(button, &QPushButton::clicked, key, [this, button, input, key]()
    {
        EWFetchUserInput fetchUserInput(input);
        fetchUserInput.exec();
        if(fetchUserInput.result() == QDialog::Rejected) { return; }

        int tempMod = fetchUserInput.getMod();
        int tempKey = fetchUserInput.getKey();
        key->update(tempMod, tempKey);

        QString keySequenceText = key->getKeySequence().toString();
        button->setText(convertText(keySequenceText, tempKey));
    });
}

QString EWHotkeyTable::convertText(QString text, int key)
{
    switch(key)
    {
    case 1:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("LMB");
        return text;
    }
    case 2:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("RMB");
        return text;
    }
    case 4:
    {
        text = text.first(text.lastIndexOf('+') + 1);
        text = text.append("MMB");
        return text;
    }
    default: { return text; }
    }
}


















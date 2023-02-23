#include "EWDirectoryButton.h"

EWDirectoryButton::EWDirectoryButton(const QString& name, const QString& path,
                                     const int indexInList, QWidget* parent) :
    QPushButton(name, parent),
    dirName(name), dirPath(path), index(indexInList)
{
    this->setFlat(true);

    connect(this, &EWDirectoryButton::clicked, this, &EWDirectoryButton::emitIndex);
}

void EWDirectoryButton::emitIndex()
{
    emit historyButtonClicked(index);
}

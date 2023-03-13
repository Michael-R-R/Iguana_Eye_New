#include "SubMenu.h"

SubMenu::SubMenu(QString title, QWidget* parent) :
    QMenu(title, parent),
    actionCollection()
{

}

SubMenu::~SubMenu()
{

}

bool SubMenu::appendAction(const QString& key, std::unique_ptr<QAction> action)
{
    if(doesExist(key))
        return false;

    this->addAction(&(*action));
    actionCollection[key] = std::move(action);

    return true;
}

bool SubMenu::removeAction(const QString& key)
{
    if(!doesExist(key))
        return false;

    actionCollection.erase(key);

    return true;
}

bool SubMenu::doesExist(const QString& key)
{
    return (actionCollection.find(key) != actionCollection.end());
}

QAction* SubMenu::getAction(const QString& key)
{
    if(!doesExist(key))
        return nullptr;

    return &(*actionCollection[key]);
}

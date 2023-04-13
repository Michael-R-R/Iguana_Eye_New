#include "SubMenu.h"

SubMenu::SubMenu(QString title, QWidget* parent) :
    QMenu(title, parent),
    actionCollection()
{

}

SubMenu::~SubMenu()
{

}

bool SubMenu::appendAction(const QString title, QAction* action)
{
    if(doesExist(title)) { return false; }
    actionCollection[title] = action;
    this->addAction(action);

    return true;
}

bool SubMenu::removeAction(const QString& title)
{
    if(!doesExist(title)) { return false; }
    auto temp = actionCollection[title];
    actionCollection.remove(title);
    delete temp;

    return true;
}

bool SubMenu::doesExist(const QString& title)
{
    return (actionCollection.find(title) != actionCollection.end());
}

void SubMenu::setAllEnabled(bool val)
{
    for(auto& i : actionCollection)
    {
        i->setEnabled(val);
    }
}

QAction* SubMenu::getAction(const QString& title)
{
    if(!doesExist(title))
        return nullptr;

    return actionCollection[title];
}

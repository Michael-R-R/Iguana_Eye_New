#pragma once

#include <QMenu>
#include <QString>
#include <QMap>
#include <QAction>

class SubMenu : public QMenu
{
    QMap<QString, QAction*> actionCollection;

public:
    SubMenu(QString title, QWidget* parent = nullptr);
    virtual ~SubMenu();

    bool appendAction(const QString title, QAction* action);
    bool removeAction(const QString& title);
    bool doesExist(const QString& title);
    void setAllEnabled(bool val);
    QAction* getAction(const QString& title);


    template<class T>
    T* findAction()
    {
        for(auto& i : actionCollection)
        {
            if(typeid(*i) == typeid(T))
            {
                return static_cast<T*>(&(*i));
            }
        }

        return nullptr;
    }
};


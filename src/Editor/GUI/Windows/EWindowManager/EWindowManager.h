#pragma once

#include <QObject>
#include <QMap>

#include "EWindow.h"

class EWindowManager : public QObject
{
    QMap<QString, EWindow*> windowCollection;

public:
    EWindowManager(QObject* parent = nullptr);
    ~EWindowManager();

    void startup();

    void showAll();
    void hideAll();
    EWindow* value(const QString &title) const;
    bool appendWindow(const QString title, EWindow* window);
    bool removeWindow(const QString& title);
    bool doesExist(const QString& title) const;

    void clear();

private:
    void setupOptionsWindow();
    void setupGlslEditorWindow();
    void setupFileExplorerWindow();
    void setupMessageLogWindow();

public:
    template<class T>
    T* findWindow() const
    {
        for(auto& i : windowCollection)
        {
            if(typeid(*i) == typeid(T))
                return static_cast<T*>(&(*i));
        }

        return nullptr;
    }
};


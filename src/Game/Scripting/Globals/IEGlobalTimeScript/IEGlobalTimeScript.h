#pragma once

#include <QObject>
#include <sol/sol.hpp>

class IETime;

class IEGlobalTimeScript : public QObject
{
    Q_OBJECT

    // DOES NOT OWN THIS POINTER
    IETime* time;

public:
    IEGlobalTimeScript();
    IEGlobalTimeScript(IETime* val, sol::table& globalTable, QObject* parent = nullptr);
    ~IEGlobalTimeScript();

public slots:
    float fps();
    float deltaTime();
};


#pragma once

#include <QObject>
#include <sol/sol.hpp>

class IEInput;

class IEGlobalInputScript : public QObject
{
    Q_OBJECT

    // DOES NOT OWN THIS POINTER
    IEInput* input;

public:
    IEGlobalInputScript(IEInput* val, sol::table& globalTable, QObject* parent = nullptr);
    ~IEGlobalInputScript();

public slots:
    bool isPressed(const char* keyName);
};


#pragma once

#include <QWidget>
#include <QMap>
#include <QVector2D>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QFocusEvent>

#include "InputKey.h"

class InputCapture : public QWidget
{
    Q_OBJECT

    QMap<InputKey, bool> capturedInput;
    InputKey lastKey;
    InputKey currKey;
    int lastMod;

    QVector2D cursorPos;

public:
    InputCapture(QWidget* parent = nullptr);
    ~InputCapture();

    void clear();
    bool checkStatus(const InputKey& key);

    const QVector2D& getCursorPos() const { return cursorPos; }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

private:
    void checkEvent(QEvent* event);

signals:
    void inputPressed(const InputKey& key);
    void inputReleased(const InputKey& key);
    void wheelDeltaChanged(const QPoint& delta);
};


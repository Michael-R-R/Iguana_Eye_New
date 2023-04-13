#pragma once

#include <QComboBox>
#include <QVector>

#include "ShaderComboBoxContextMenu.h"

class IEShaderManager;

class EWShaderComboBox : public QComboBox
{
    Q_OBJECT

    QVector<unsigned long long> fullIdList;

    ShaderComboBoxContextMenu* contextMenu;

public:
    EWShaderComboBox(QWidget* parent = nullptr);
    ~EWShaderComboBox();

    bool eventFilter(QObject* watched, QEvent* event) override;
    void startup();
    void selectShader(const unsigned long long key);
    unsigned long long getSelectedId();

private:
    void initialBuild(IEShaderManager* shaderManager);
    bool indexBoundCheck(const int index);
    bool doesExist(const unsigned long long key);
    QString checkForDuplicateName(const QString& nameToCheck);

private slots:
    void currentShaderChanged(int index);
    void addShader(const unsigned long long key, const QString& path);
    void removeShader(const unsigned long long key);
    void changeShaderKey(const unsigned long long oldKey, const unsigned long long newKey);
    void showCustomContextMenu(const QPoint& pos);

signals:
    void cleared();
    void vertexSrcSelected(const QString& vSrc);
    void fragmentSrcSelected(const QString& fSrc);
};


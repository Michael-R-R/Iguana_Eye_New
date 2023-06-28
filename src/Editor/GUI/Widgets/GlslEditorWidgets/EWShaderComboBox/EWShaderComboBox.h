#pragma once

#include <QComboBox>
#include <QVector>

#include "ShaderComboBoxContextMenu.h"

class IEShaderManager;

class EWShaderComboBox : public QComboBox
{
    Q_OBJECT

    QVector<uint64_t> fullIdList;

    ShaderComboBoxContextMenu* contextMenu;

public:
    EWShaderComboBox(QWidget* parent = nullptr);
    ~EWShaderComboBox();

    bool eventFilter(QObject* watched, QEvent* event) override;
    void startup();
    void selectShader(const uint64_t key);
    uint64_t getSelectedId();

private:
    void initialBuild(IEShaderManager* shaderManager);
    bool indexBoundCheck(const int index);
    bool doesExist(const uint64_t key);
    QString checkForDuplicateName(const QString& nameToCheck);

private slots:
    void currentShaderChanged(int index);
    void addShader(const uint64_t key, const QString& path);
    void removeShader(const uint64_t key);
    void changeShaderKey(const uint64_t oldKey, const uint64_t newKey);
    void showCustomContextMenu(const QPoint& pos);

signals:
    void cleared();
    void vertexSrcSelected(const QString& vSrc);
    void fragmentSrcSelected(const QString& fSrc);
};


#pragma once

#include <QFileIconProvider>

class EWFileExplorerIconProvider : public QFileIconProvider
{
    QIcon folderIcon;
    QIcon glslFileIcon;
    QIcon basicFileIcon;

public:
    EWFileExplorerIconProvider();
    ~EWFileExplorerIconProvider() {}

protected:
    QIcon icon(const QFileInfo& info) const override;
};


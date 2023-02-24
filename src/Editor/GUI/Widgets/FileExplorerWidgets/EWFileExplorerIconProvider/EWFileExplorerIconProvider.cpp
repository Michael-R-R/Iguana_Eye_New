#include "EWFileExplorerIconProvider.h"

EWFileExplorerIconProvider::EWFileExplorerIconProvider() :
    QFileIconProvider(),
    folderIcon(),
    glslFileIcon(),
    basicFileIcon()
{
    folderIcon.addFile(":/FileExplorer/FileExplorer/Folder.png", QSize(), QIcon::Selected);
    glslFileIcon.addFile(":/FileExplorer/FileExplorer/Document_glsl.png", QSize(), QIcon::Selected);
    basicFileIcon.addFile(":/FileExplorer/FileExplorer/Document_default.png", QSize(), QIcon::Selected);
}

QIcon EWFileExplorerIconProvider::icon(const QFileInfo& info) const
{
    if(info.isDir())
        return folderIcon;
    if(info.fileName().contains(".glsl"))
        return glslFileIcon;
    else
        return basicFileIcon;
}

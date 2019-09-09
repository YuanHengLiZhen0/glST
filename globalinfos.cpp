#include "globalinfos.h"
#include <QFileInfo>
#include <QDir>

QString GlobalInfos::sCurrentWorkspacePath = "";

QFont GlobalInfos::sTitleFont = QFont("Songti", 15, QFont::Bold);

QString GlobalInfos::getCurrentWorkspacePath()
{
    return sCurrentWorkspacePath;
}

void GlobalInfos::setCurrentWorkspacePath(const QString& path)
{
    QFileInfo fInfo(path);
    if (fInfo.isFile())
        sCurrentWorkspacePath = fInfo.dir().absolutePath();
    else if (fInfo.isDir())
        sCurrentWorkspacePath = fInfo.absoluteFilePath();
    else
    {
        QDir defaultWorkspace = QDir("temp/workspace");
        sCurrentWorkspacePath = defaultWorkspace.absolutePath();
        if (!defaultWorkspace.exists())
        {
            QDir().mkpath(sCurrentWorkspacePath);
        }
    }
}

QFont& GlobalInfos::getTitleFont()
{
    return sTitleFont;
}

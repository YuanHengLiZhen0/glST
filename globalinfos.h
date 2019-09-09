#ifndef GLOBALINFOS_H
#define GLOBALINFOS_H

#include <QString>
#include <QFont>

class GlobalInfos
{
public:
    static QString getCurrentWorkspacePath();

    static void setCurrentWorkspacePath(const QString& path);

    static QFont& getTitleFont();

private:
    static QString sCurrentWorkspacePath;

    static QFont sTitleFont;

};

#endif // GLOBALINFOS_H

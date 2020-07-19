#ifndef UTIL_H
#define UTIL_H

#include <QTime>
#include <QFileInfo>

class QString;

class Util
{
public:
    static QString getDisplayTime(const QString &xFileName);
    static QString getDisplayTime(uint xTimeMSec);
    static uint getTimeMSec(const QString &xFileName);
    Q_INVOKABLE static QString getAppConfigLocation();
    Q_INVOKABLE static QString getCacheLocation();
    Q_INVOKABLE static QString getMusicLocation();
    Q_INVOKABLE static QString getHomeLocation();
    Q_INVOKABLE static QString appendFile(QString &xString);
};

#endif // UTIL_H

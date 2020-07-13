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

};

#endif // UTIL_H

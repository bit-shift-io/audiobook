#ifndef UTIL_H
#define UTIL_H

#include <QTime>
#include <QFileInfo>

class QString;

class Util
{
public:
    static QString getDisplayTime(uint p_time);
    static uint getTimeMSec(const QString &p_filename);

    static QTime get_time(const QString &p_filename);
    static QTime add_time(QTime &a, QTime &b);

};

#endif // UTIL_H

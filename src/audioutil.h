#ifndef AudioUtil_H
#define AudioUtil_H

#include <QString>
#include <QTime>

class AudioUtil
{
public:
    static QString get_display_time(uint p_time);
    static uint get_time_msec(const QString &p_filename);

    static QTime get_time(const QString &p_filename);
    static QTime add_time(QTime &a, QTime &b);
};

#endif // AudioUtil_H

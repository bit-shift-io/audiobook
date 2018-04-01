#ifndef AUDIOHELPER_H
#define AUDIOHELPER_H

#include <QString>
#include <QTime>

class AudioHelper
{
public:
    static QString get_display_time(uint p_time);
    static uint get_time_msec(const QString &p_filename);

    static QTime get_time(const QString &p_filename);
    static QTime add_time(QTime &a, QTime &b);
};

#endif // AUDIOHELPER_H

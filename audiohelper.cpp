#include "audiohelper.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>



QString AudioHelper::get_display_time(uint p_time) {
    //uint milliseconds = p_time%1000;
    uint seconds = (p_time/1000)%60;
    uint minutes = (p_time/(1000*60))%60;
    uint hours = (p_time/(1000*60*60)); //%24;
    QString str_hours = (hours < 10) ? "0" + QString::number(hours) : QString::number(hours);
    QString str_minutes = (minutes < 10) ? "0" + QString::number(minutes) : QString::number(minutes);
    QString str_seconds = (seconds < 10) ? "0" + QString::number(seconds) : QString::number(seconds);
    QString t(str_hours + ":" + str_minutes + ":" + str_seconds);
    return t;
}

uint AudioHelper::get_time_msec(const QString &p_filename) {
    TagLib::FileRef f(p_filename.toUtf8().constData());
    uint len = f.file()->audioProperties()->lengthInMilliseconds();
    return len;
}


// OLD
QTime AudioHelper::get_time(const QString &p_filename) {

    TagLib::FileRef f(p_filename.toUtf8().constData());
    QTime time(0,0,0,0);
    int len = f.file()->audioProperties()->lengthInSeconds();
    time = time.addSecs(len);
    //time = time.addSecs(f.audioProperties()->lengthInSeconds());
    return time;
}

QTime AudioHelper::add_time(QTime &a, QTime &b) {
    QTime time(a.hour()+b.hour(),a.minute()+b.minute(),a.second() + b.second(),a.msec()+b.msec());
    return time;
}



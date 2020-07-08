#include "audioutil.h"
#include "taglib/fileref.h"


QString AudioUtil::get_display_time(uint p_time) {
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


uint AudioUtil::get_time_msec(const QString &p_filename) {
    TagLib::FileRef f(p_filename.toUtf8().constData());
    uint len = f.file()->audioProperties()->lengthInMilliseconds();
    return len;
}

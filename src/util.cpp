#include <QStandardPaths>
#include "util.h"
#include "taglib/fileref.h"


QString Util::getDisplayTime(const QString &xFileName)
{
    uint t = getTimeMSec(xFileName);
    return getDisplayTime(t);
}

QString Util::getDisplayTime(uint xTimeMSec) {
    //uint milliseconds = p_time%1000;
    uint seconds = (xTimeMSec/1000)%60;
    uint minutes = (xTimeMSec/(1000*60))%60;
    uint hours = (xTimeMSec/(1000*60*60)); //%24;
    QString str_hours = (hours < 10) ? "0" + QString::number(hours) : QString::number(hours);
    QString str_minutes = (minutes < 10) ? "0" + QString::number(minutes) : QString::number(minutes);
    QString str_seconds = (seconds < 10) ? "0" + QString::number(seconds) : QString::number(seconds);
    QString t(str_hours + ":" + str_minutes + ":" + str_seconds);
    return t;
}


uint Util::getTimeMSec(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    uint len = f.file()->audioProperties()->lengthInMilliseconds();
    return len;
}

QString Util::getAppConfigLocation()
{
    return QStandardPaths::locate(QStandardPaths::AppConfigLocation, QString(), QStandardPaths::LocateDirectory);
}

QString Util::getCacheLocation()
{
    return QStandardPaths::locate(QStandardPaths::CacheLocation, QString(), QStandardPaths::LocateDirectory);
}

QString Util::getMusicLocation()
{
    return QStandardPaths::locate(QStandardPaths::MusicLocation, QString(), QStandardPaths::LocateDirectory);
}

QString Util::getHomeLocation()
{
    return QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
}

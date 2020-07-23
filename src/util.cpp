#include <QStandardPaths>
#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QDir>
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


QString Util::getTagTitle(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    QString len = QString(f.file()->tag()->title().toCString());
    return len;
}


QString Util::getTagAlbum(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    QString len = QString(f.file()->tag()->album().toCString());
    return len;
}


QString Util::getTagArtist(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    QString len = QString(f.file()->tag()->artist().toCString());
    return len;
}

QString Util::getTagGenre(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    QString len = QString(f.file()->tag()->genre().toCString());
    return len;
}

QString Util::toCamelCase(const QString &xString)
{
    QStringList parts = xString.split(' ', QString::SkipEmptyParts);
    for (int i = 0; i < parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());
    return parts.join(" ");
}

int Util::getTagYear(const QString &xFileName) {
    TagLib::FileRef f(xFileName.toUtf8().constData());
    int len = f.file()->tag()->year();
    return len;
}


QString Util::getAppConfigLocation()
{
    // find + create the folder
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if (!dir.exists())
        dir.mkpath(".");
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
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
#ifdef Q_OS_ANDROID
    // GenericDataLocation = user folder
    //QStringList systemEnvironment = QProcess::systemEnvironment();
    //qDebug() << systemEnvironment;
    //qDebug() << QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory);
    return QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory);
#endif
    return QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
}

QString Util::appendFile(QString &xString) {
    return QString("file://" + xString);
}

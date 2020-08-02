#ifndef UTIL_H
#define UTIL_H

#include <QTime>
#include <QFileInfo>

class QString;
class QQmlEngine;
class QJSEngine;

class Util : public QObject
{
    Q_OBJECT

public:
    Util(const Util&) = delete; // disable copy for singleton
    static Util *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    static QString getDisplayTime(const QString &xFileName);
    static QString getDisplayTime(uint xTimeMSec);
    static uint getTimeMSec(const QString &xFileName);
    static QString getTagTitle(const QString &xFileName);
    static QString getTagAlbum(const QString &xFileName);
    static QString getTagArtist(const QString &xFileName);
    static int getTagYear(const QString &xFileName);
    static QString getTagGenre(const QString &xFileName);
    static QString toCamelCase(const QString &xString);
    Q_INVOKABLE static QString getAppConfigLocation();
    Q_INVOKABLE static QString getCacheLocation();
    Q_INVOKABLE static QString getMusicLocation();
    Q_INVOKABLE static QString getHomeLocation();
    Q_INVOKABLE static QStringList getAndroidStorageLocations();
    Q_INVOKABLE static QString appendFile(QString &xString);

private:
    explicit Util(QObject *parent = nullptr);
};

#endif // UTIL_H

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QtCore>
#include <QSettings>

class QQmlEngine;
class QJSEngine;

class Settings : public QSettings
{
    Q_OBJECT

public:
    Settings(const Settings&) = delete; // disable copy for singleton

    static Settings *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value) { QSettings::setValue(key, value); }
    Q_INVOKABLE inline QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const { return QSettings::value(key, defaultValue); }
    Q_INVOKABLE inline bool valueBool(const QString &key, const QVariant &defaultValue = QVariant()) const { return QSettings::value(key, defaultValue).toBool(); }

private:
    explicit Settings(QObject *parent = 0) : QSettings(QSettings::UserScope,
        QCoreApplication::instance()->organizationName(),
        QCoreApplication::instance()->applicationName(),
        parent) {} // private for singleton

};


#endif // SETTINGS_H

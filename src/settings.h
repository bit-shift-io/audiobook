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

    // Q_INVOKABLE - allow qml to access non-slot functions
    Q_INVOKABLE inline static void setValue(const QString &xKey, const QVariant &xValue) {instance()->setValueImp(xKey, xValue);};
    Q_INVOKABLE inline static QVariant value(const QString &xKey, const QVariant &xDefaultValue = QVariant()) { return instance()->valueImp(xKey, xDefaultValue); }
    Q_INVOKABLE inline static bool valueBool(const QString &xKey, const QVariant &xDefaultValue = QVariant()) { return instance()->valueImp(xKey, xDefaultValue).toBool(); }
    Q_INVOKABLE inline static QString fileName() { return instance()->fileNameImp();};

private:
    explicit Settings(QObject *parent = 0); // private for singleton

    // implementations
    inline void setValueImp(const QString &xKey, const QVariant &xValue) { QSettings::setValue(xKey, xValue); }
    inline QVariant valueImp(const QString &xKey, const QVariant &xDefaultValue = QVariant()) const { return QSettings::value(xKey, xDefaultValue); }
    inline bool valueBoolImp(const QString &xKey, const QVariant &xDefaultValue = QVariant()) const { return QSettings::value(xKey, xDefaultValue).toBool(); }
    inline QString fileNameImp() const { return QSettings::fileName(); }
};


#endif // SETTINGS_H

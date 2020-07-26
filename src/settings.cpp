#include "settings.h"


Settings *Settings::instance()
{
    static Settings* instance = new Settings();
    return instance;
}

QObject *Settings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    // C++ and QML instance they are the same instance
    return Settings::instance();
}

Settings::Settings(QObject *parent)
    : QSettings(QSettings::Format::IniFormat,
                QSettings::UserScope,
                QCoreApplication::instance()->organizationName(),
                QCoreApplication::instance()->applicationName(),
                parent)
{
}

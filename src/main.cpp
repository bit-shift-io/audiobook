#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDirIterator>
#include <QDebug>
#include <QQmlDebuggingEnabler>
#include <QIcon>

#include "settings.h"

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#include <QtSvg>    //Because deployment sometimes just forgets to include this lib otherwise
//#include "./3rdparty/kirigami/src/kirigamiplugin.h"
#endif

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // used for settings
    app.setOrganizationName("bitshift");
    app.setOrganizationDomain("bitshift");
    app.setApplicationName("AudioBook");
    app.setWindowIcon(QIcon(":/bitshift.audiobook.png"));

#ifdef Q_OS_ANDROID
    //KirigamiPlugin::getInstance().registerTypes();
#endif

    // get instance in C++
    //Settings *settings = Settings::instance();
    //Database *database = Database::instance();
    //FileIO *fileio = FileIO::instance();

    // register types
    //qmlRegisterSingletonType<Database>("Database", 1, 0, "Database", &Database::qmlInstance);
    //qmlRegisterSingletonType<Database>("FileIO", 1, 0, "FileIO", &FileIO::qmlInstance);
    qmlRegisterSingletonType<Settings>("QSettings", 1, 0, "QSettings", &Settings::qmlInstance);

    //qmlRegisterType<Weather>("Weather", 1, 0, "Weather");
    //qmlRegisterType<ForecastModel>("Forecast", 1, 0, "ForecastModel");
    //qmlRegisterType<RadarImage>("RadarImage", 1, 0, "RadarImage");


    // add imports
    engine.addImportPath(".");
    engine.addImportPath("./lib");
    engine.addImportPath("./plugin");
    engine.addImportPath("./qml");
    engine.addImportPath("qrc:/qml");

    // load qml
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    // debug, print qrc resources
    if (false) {
        QDirIterator it(":/", QDirIterator::Subdirectories);
        while (it.hasNext()) {
            qDebug() << it.next();
        }
    }


#ifdef Q_OS_ANDROID
    // hide splash screen
    QtAndroid::hideSplashScreen(); // optional fade duration in ms
#endif

    return app.exec();
}

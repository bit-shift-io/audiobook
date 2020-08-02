#include <QGuiApplication>
//#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDirIterator>
#include <QDebug>
#include <QQmlDebuggingEnabler>
#include <QIcon>
#include <QQmlContext>

#include "settings.h"
#include "database.h"
#include "librarymodel.h"
#include "libraryfilterproxy.h"
#include "chaptermodel.h"
#include "player.h"
#include "shortcuts.h"
#include "util.h"

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#include <QtSvg>    //Because deployment sometimes just forgets to include this lib otherwise
//#include "./3rdparty/kirigami/src/kirigamiplugin.h"
#include <QtAndroid>

// these also need to be in the android manifest xml
const QVector<QString> permissions({"android.permission.WRITE_EXTERNAL_STORAGE",
                                    "android.permission.READ_EXTERNAL_STORAGE"});
#endif

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QApplication app(argc, argv);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // used for settings
    app.setOrganizationName("bitshift");
    app.setOrganizationDomain("bitshift");
    app.setApplicationName("AudioBook");
    app.setWindowIcon(QIcon(":/bitshift.audiobook.png"));

#ifdef Q_OS_ANDROID
    //Request requiered permissions at runtime
    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return 0;
        }
    }
    //KirigamiPlugin::getInstance().registerTypes();
#endif


    // create singletons
    Settings* settings = Settings::instance();
    Database* database = Database::instance();
    Player* player = Player::instance();
    Shortcuts * shortcuts = Shortcuts::instance();

    // library model proxy for filtering search
    // https://doc.qt.io/archives/qt-5.10/qtquickcontrols-filesystembrowser-example.html
    LibraryModel *library_model = new LibraryModel();
    LibraryFilterProxy *filter_proxy = new LibraryFilterProxy();
    filter_proxy->setSourceModel(library_model);


    ChapterModel *chapter_model = new ChapterModel();

    // register types
    qmlRegisterSingletonType<Settings>("QSettings", 1, 0, "QSettings", &Settings::qmlInstance);
    qmlRegisterSingletonType<Database>("Database", 1, 0, "Database", &Database::qmlInstance);
    qmlRegisterSingletonType<Player>("Player", 1, 0, "Player", &Player::qmlInstance);
    qmlRegisterSingletonType<Util>("Util", 1, 0, "Util", &Util::qmlInstance);


    qmlRegisterType<ChapterModel>("ChapterModel", 1, 0, "ChapterModel");
    engine.rootContext()->setContextProperty("LibraryFilterProxy", filter_proxy);

    //qmlRegisterUncreatableType<FileProxyModel>("FileProxyModel", 1, 0, "FileProxyModel", "Cannot create a FileSystemModel instance.");
    //engine.rootContext()->setContextProperty("FileProxyModel", file_proxy_model);

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

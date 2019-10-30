#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

/*
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationDomain(APP_URL);
    QCoreApplication::setWindowIcon(QIcon(APP_ICON_PATH));
    */

    QCoreApplication::setApplicationName(QStringLiteral("AudioBook"));
    QCoreApplication::setApplicationVersion( QLatin1String(QT_VERSION_STR));
    QCoreApplication::setOrganizationName(QStringLiteral("bitshift"));
    QCoreApplication::setOrganizationDomain("bitshift.io");
    QGuiApplication::setApplicationDisplayName(QStringLiteral("AudioBook"));

    MainWindow *main_window = new MainWindow();
    main_window->show();

    return app.exec();
} 

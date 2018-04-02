#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Audio Book"));
    QCoreApplication::setApplicationVersion( QLatin1String(QT_VERSION_STR));
    QCoreApplication::setOrganizationName(QStringLiteral("bit-shift"));
    QCoreApplication::setOrganizationDomain("bit-shift.io");
    QGuiApplication::setApplicationDisplayName(QStringLiteral("Audio Book"));

    MainWindow *main_window = new MainWindow();
    main_window->show();

    return app.exec();
} 

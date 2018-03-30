#include "player.h"
#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QSettings>
#include <QIcon>
#include <QDir>
#include <QUrl>

static bool associateFileTypes()
{
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    const QString key = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\") + fileName;
    QSettings settings(key, QSettings::NativeFormat);
    if (settings.status() != QSettings::NoError) {
        qWarning() << "Cannot access registry key" << key;
        return false;
    }
    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);

    settings.beginGroup(QStringLiteral("SupportedTypes"));
    QMimeDatabase mimeDatabase;
    const QStringList supportedMimeTypes = Player::supportedMimeTypes();
    for (const QString &fileType : supportedMimeTypes) {
        const QStringList suffixes = mimeDatabase.mimeTypeForName(fileType).suffixes();
        for (QString suffix : suffixes) {
            suffix.prepend('.');
            settings.setValue(suffix, QString());
        }
    }
    settings.endGroup();

    settings.beginGroup(QStringLiteral("shell"));
    settings.beginGroup(QStringLiteral("open"));
    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);
    settings.beginGroup(QStringLiteral("Command"));
    settings.setValue(QStringLiteral("."),
                      QLatin1Char('"') + QDir::toNativeSeparators(filePath) + QStringLiteral("\" \"%1\""));

    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Audio Book"));
    QCoreApplication::setApplicationVersion( QLatin1String(QT_VERSION_STR));
    QCoreApplication::setOrganizationName(QStringLiteral("bit-shift"));
    QCoreApplication::setOrganizationDomain("bit-shift.io");
    QGuiApplication::setApplicationDisplayName(QStringLiteral("Audio Book"));

    //if (!associateFileTypes())
    //    return -1;

    QCommandLineParser parser;
    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral("url"), Player::tr("The URL to open."));
    parser.process(app);


    MainWindow *main_window = new MainWindow();
    //if (!parser.positionalArguments().isEmpty())
    //    main_window.loadFile(parser.positionalArguments().first());
    //      player.playUrl(QUrl::fromUserInput(parser.positionalArguments().constFirst(), QDir::currentPath(), QUrl::AssumeLocalFile));
    main_window->show();

    return app.exec();
} 

#include "mainwindow.h"
#include "audioplayer.h"
#include "ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    audio_player = new AudioPlayer();
    //playlist = new Playlist();

    // connect buttons to ui
    connect(ui->button_play_pause, SIGNAL(clicked()), this, SLOT(play_pause()));
    connect(ui->button_settings, SIGNAL(clicked()), this, SLOT(open_file()));

    // theme buttons
    ui->button_play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_play_pause->setToolTip(tr("Play | Pause"));
    ui->button_play_pause->setFixedSize(ui->button_play_pause->sizeHint());
    ui->button_settings->setText(tr(""));

    ui->button_settings->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_settings->setToolTip(tr("Open a file..."));
    ui->button_settings->setFixedSize(ui->button_settings->sizeHint());
    ui->button_settings->setText(tr("..."));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bookmark()
{

}

void MainWindow::play_pause()
{
    audio_player->togglePlayback();
}

void MainWindow::open_file()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open File"));
    fileDialog.setMimeTypeFilters(AudioPlayer::supportedMimeTypes());
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        audio_player->playUrl(fileDialog.selectedUrls().constFirst());
}

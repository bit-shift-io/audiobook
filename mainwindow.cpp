#include "mainwindow.h"
#include "player.h"
#include "library.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "librarymodel.h"
#include "audiohelper.h"
#include "stretchingheader.h"
#include <QtWidgets>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    player = new Player();
    library = new Library();
    settings = new Settings();

    // play/pause
    ui->button_play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_play_pause->setToolTip(tr("Play"));

    // rewind
    ui->button_rewind->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    ui->button_rewind->setToolTip(tr("Back 30s"));
    //ui->button_rewind->setFixedSize(ui->button_rewind->sizeHint());

    // settings
    ui->button_settings->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
    ui->button_settings->setToolTip(tr("Settings"));
    //ui->button_settings->setFixedSize(ui->button_settings->sizeHint());
    ui->button_settings->setPopupMode(QToolButton::InstantPopup);

    QMenu *menu_settings = new QMenu();
    QAction *action_library = new QAction(tr("&Library"),this);
    action_library->setStatusTip(tr("Change library path"));
    menu_settings->addAction(action_library);

    QAction *action_quit = new QAction(tr("&Quit"),this);
    action_quit->setStatusTip(tr("Quit"));
    menu_settings->addAction(action_quit);

    ui->button_settings->setMenu(menu_settings);

    // chapter/bookmarks button
    ui->button_chapters->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    ui->button_chapters->setPopupMode(QToolButton::InstantPopup);
    QMenu *menu_chapters = new QMenu();
    QAction *act0 = new QAction("chapter 01",this);
    act0->setObjectName("act0");
    menu_chapters->addAction(act0);
    ui->button_chapters->setMenu(menu_chapters);

    // library view/table
    LibraryModel *library_model = new LibraryModel(0,library);
    ui->view_library->setModel(library_model);
    ui->view_library->verticalHeader()->hide();

    StretchingHeader *header = new StretchingHeader(Qt::Horizontal, ui->view_library);
    header->setStretchFactors(StretchFactors() << 4 << 1 << 1);
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setStretchLastSection(true);
    ui->view_library->setHorizontalHeader(header);
    connect(ui->view_library, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(play_selected_book(QModelIndex)));

    // connect buttons to ui
    connect(ui->button_play_pause, &QToolButton::clicked, player, &Player::toggle_play_pause);

    //connect(ui->slider_progress, &QSlider::valueChanged, this, &MainWindow::set_position);
    connect(ui->slider_volume, &QSlider::valueChanged, player, &Player::setVolume);

    connect(action_library, &QAction::triggered, this,  &MainWindow::pick_library_directory);
    connect(action_quit, &QAction::triggered, this, &QCoreApplication::quit);

    // connect media player
    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::update_media_state);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::update_position);
    connect(player, &QMediaPlayer::mediaChanged, this, &MainWindow::update_media_info);


    create_shortcuts();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bookmark() {

}

void MainWindow::play_selected_book(QModelIndex idx) {
    const Book &book = library->get_book_list().at(idx.row());
    player->play_book(book);
}

void MainWindow::update_media_state() {
    if (player->state() == QMediaPlayer::PausedState) {
        ui->button_play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->button_play_pause->setToolTip(tr("Play"));
    }
    else {
        ui->button_play_pause->setToolTip(tr("Pause"));
        ui->button_play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
}

void MainWindow::update_media_info() {
    ui->label_track_time->setText(AudioHelper::get_display_time(player->get_playlist_length()));
}

void MainWindow::update_position(qint64 position) {
    ui->slider_progress->setValue(player->get_progress());
    ui->label_track_position->setText(AudioHelper::get_display_time(position));
}

void MainWindow::update_duration(qint64 duration) {
    ui->slider_progress->setRange(0, duration);
    ui->slider_progress->setEnabled(duration > 0);
    ui->slider_progress->setPageStep(duration / 10);
    update_info();
}

void MainWindow::set_position(int position) {
    // avoid seeking when the slider value change is triggered from update_position()
    //if (qAbs(player->position() - position) > 99)
        player->setPosition(position);
}


void MainWindow::update_info() {
    ui->label_track_time->setText(AudioHelper::get_display_time((player->duration())));
}

void MainWindow::pick_library_directory() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Library"),
                                                    QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    library->set_library_directory(dir);
}

void MainWindow::quit() {
    QCoreApplication::quit();
}

void MainWindow::create_shortcuts() {

    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, this);
    connect(quitShortcut, &QShortcut::activated, this, &QCoreApplication::quit);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &MainWindow::pick_library_directory);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, player, &Player::toggle_play_pause);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, player, &Player::seek_forward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, player, &Player::seek_backward);

    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
    connect(increaseShortcut, &QShortcut::activated, player, &Player::increase_volume);

    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
    connect(decreaseShortcut, &QShortcut::activated, player, &Player::decrease_volume);
}


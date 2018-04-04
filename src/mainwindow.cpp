#include "mainwindow.h"
#include "player.h"
#include "library.h"
#include "ui_mainwindow.h"
#include "librarymodel.h"
#include "audioutil.h"
#include "book.h"
#include "stretchingheader.h"
#include <QtWidgets>
#include <QShortcut>
#include <QFontDatabase>
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    // add fonts
    int id = QFontDatabase::addApplicationFont(":/fonts/font_awesome");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(family);

    // setup classes
    player = new Player();
    library = new Library();

    // play/pause
    ui->button_play_pause->setText(QChar(0xf04b));
    ui->button_play_pause->setToolTip("Play");

    // seek back
    ui->button_seek_back->setFont(font);
    ui->button_seek_back->setText(QChar(0xf04a));
    ui->button_seek_back->setToolTip("Back 30 seconds");

    // seek forward
    ui->button_seek_forward->setFont(font);
    ui->button_seek_forward->setText(QChar(0xf04e));
    ui->button_seek_forward->setToolTip("Forward 30 seconds");

    // repeat
    ui->button_repeat->setFont(font);
    ui->button_repeat->setText(QChar(0xf2ea));
    ui->button_repeat->setToolTip("Repeat");

    // settings
    ui->button_settings->setFont(font);
    ui->button_settings->setText(QChar(0xf0c9));
    ui->button_settings->setToolTip("Settings");
    ui->button_settings->setPopupMode(QToolButton::InstantPopup);

    QMenu *menu_settings = new QMenu();
    QAction *action_library = new QAction(tr("&Library"),this);
    menu_settings->addAction(action_library);

    QAction *action_about = new QAction(tr("&About"),this);
    menu_settings->addAction(action_about);

    QAction *action_quit = new QAction(tr("&Quit"),this);
    menu_settings->addAction(action_quit);

    ui->button_settings->setMenu(menu_settings);

    // chapter/bookmarks button
    ui->button_chapters->setFont(font);
    ui->button_chapters->setText(QChar(0xf02e));
    ui->button_chapters->setToolTip("Chapters");
    ui->button_chapters->setPopupMode(QToolButton::InstantPopup);

    // library view/table
    LibraryModel *library_model = new LibraryModel(0,library);
    ui->view_library->setModel(library_model);
    ui->view_library->verticalHeader()->hide();

    StretchingHeader *header = new StretchingHeader(Qt::Horizontal, ui->view_library);
    header->setStretchFactors(StretchFactors() << 4 << 1 << 1);
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setStretchLastSection(true);
    ui->view_library->setHorizontalHeader(header);
    connect(ui->view_library, &QTableView::doubleClicked, this, &MainWindow::play_selected_book);

    // connect buttons to ui
    connect(ui->button_play_pause, &QToolButton::clicked, player, &Player::toggle_play_pause);
    connect(ui->button_repeat, &QToolButton::clicked, player, &Player::toggle_repeat);

    //connect(ui->slider_progress, &QSlider::valueChanged, this, &MainWindow::set_position);
    connect(ui->slider_volume, &QSlider::valueChanged, player, &Player::setVolume);

    connect(action_library, &QAction::triggered, this,  &MainWindow::pick_library_directory);
    connect(action_quit, &QAction::triggered, this, &QCoreApplication::quit);
    connect(action_about, &QAction::triggered, this, &MainWindow::open_about_url);

    // connect media player
    connect(player, &Player::stateChanged, this, &MainWindow::update_media_state);
    connect(player, &Player::positionChanged, this, &MainWindow::update_position);
    connect(player, &Player::mediaChanged, this, &MainWindow::update_media_info);
    connect(player, &Player::playback_mode_changed, this, &MainWindow::update_playback_mode);

    create_shortcuts();
    read_settings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bookmark() {

}

void MainWindow::open_about_url() {
    QUrl url("http://bit-shift.io");
    QDesktopServices::openUrl(url);
}

void MainWindow::play_selected_book(QModelIndex idx) {
    const Book& book = library->get_book_list().at(idx.row());
    player->set_playing_book(book);
    player->play();
    write_settings();
}

void MainWindow::set_playing_book(const QString &book_directory) {
    const Book* book = library->find_by_directory(book_directory);
    if(!book)
        return;
    int index = library->get_book_index(*book);
    ui->view_library->selectRow(index);
    player->set_playing_book(*book);
}

void MainWindow::set_playing_chapter() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        qDebug() << action->text();
        player->set_playing_chapter(action->text());
    }
}

void MainWindow::update_playback_mode() {
    if (player->playlist()->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential) {
        ui->button_repeat->setText(QChar(0xf161));
        ui->button_repeat->setToolTip(tr("Repeat"));
    }
    else {
        ui->button_repeat->setToolTip(tr("Sequential"));
        ui->button_repeat->setText(QChar(0xf2ea));
    }
}

void MainWindow::update_media_state() {
    if (player->state() == QMediaPlayer::PausedState) {
        ui->button_play_pause->setText(QChar(0xf04b));
        ui->button_play_pause->setToolTip(tr("Play"));
    }
    else {
        ui->button_play_pause->setToolTip(tr("Pause"));
        ui->button_play_pause->setText(QChar(0xf04c));
    }
}

void MainWindow::update_media_info() {
    const Book& book = player->get_playing_book();
    ui->label_track_time->setText(AudioUtil::get_display_time(player->get_playlist_length()));
    ui->label_book_title->setText(book.title);
    setWindowTitle(book.title);

    // get list of chapters
    QMenu *menu_chapters = new QMenu();
    ui->button_chapters->setMenu(menu_chapters);

    for (auto chapter : book.chapter_titles) {
        QAction *action = new QAction(chapter,this);
        menu_chapters->addAction(action);
        connect(action, &QAction::triggered, this,  &MainWindow::set_playing_chapter);
    }
}

void MainWindow::update_position(qint64 position) {
    ui->slider_progress->setValue(player->get_progress());
    ui->label_track_position->setText(AudioUtil::get_display_time(player->get_position()));
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
    ui->label_track_time->setText(AudioUtil::get_display_time((player->duration())));
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

void MainWindow::write_settings() {
    QSettings settings("bit-shift", "audio book");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    settings.beginGroup("Library");
    settings.setValue("library_directory", library->get_library_directory());
    settings.endGroup();

    settings.beginGroup("Player");
    settings.setValue("playing_book_directory", player->get_playing_book().directory);
    settings.endGroup();

}

void MainWindow::read_settings() {
    QSettings settings("bit-shift", "audio book");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(600, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    settings.beginGroup("Library");
    QString dir = settings.value("library_directory", QDir::homePath()).toString();
    library->set_library_directory(dir);
    settings.endGroup();

    settings.beginGroup("Player");
    QString playing_book_dir = settings.value("playing_book_directory", "").toString();
    set_playing_book(playing_book_dir);
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    write_settings();
    event->accept();
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

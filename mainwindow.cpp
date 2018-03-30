#include "mainwindow.h"
#include "player.h"
#include "library.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "librarymodel.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    player = new Player();
    library = new Library();
    settings = new Settings();

    // connect buttons to ui
    connect(ui->button_play_pause, SIGNAL(clicked()), this, SLOT(play_pause()));
    connect(ui->button_settings, SIGNAL(clicked()), this, SLOT(pick_library_directory()));

    // theme buttons
    ui->button_play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_play_pause->setToolTip(tr("Play | Pause"));
    ui->button_play_pause->setFixedSize(ui->button_play_pause->sizeHint());
    ui->button_settings->setText(tr(""));

    ui->button_settings->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_settings->setToolTip(tr("Open a file..."));
    ui->button_settings->setFixedSize(ui->button_settings->sizeHint());
    ui->button_settings->setText(tr("..."));

    // library view/table
    LibraryModel *library_model = new LibraryModel(0,library);
    ui->view_library->setModel(library_model);
    ui->view_library->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view_library->verticalHeader()->hide();

   // QItemSelectionModel *sm = ui->view_library->selectionModel();
   // connect(sm, SIGNAL(doubleClicked(QModelIndex,QModelIndex)),this, SLOT(on_tableViewTriggerSelectionModel_currentRowChanged(QModelIndex,QModelIndex)));

    connect(ui->view_library, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(play_selected_book(QModelIndex)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bookmark()
{

}

void MainWindow::play_selected_book(QModelIndex idx)
{
    const Book &book = library->get_book_list().at(idx.row());
    player->play_book(book);
}

void MainWindow::play_pause()
{
    player->toggle_play_pause();
}

void MainWindow::pick_library_directory()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Library"),
                                                    QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    library->set_library_directory(dir);
}

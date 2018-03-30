#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class Player;
class Library;
class Settings;
class LibraryModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Player *player;
    Library *library;
    Settings *settings;

private:
    Ui::MainWindow *ui;

public slots:
    void play_pause();
    void bookmark();
    void pick_library_directory();
    void play_selected_book(QModelIndex idx);

signals:
    void volume_changed();
};

#endif // MAINWINDOW_H



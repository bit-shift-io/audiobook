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
    void set_position(int position);
    void set_volume(int volume);
    void update_position(qint64 position);
    void update_duration(qint64 duration);
    void update_info();
    void create_shortcuts();
    void quit();

};

#endif // MAINWINDOW_H



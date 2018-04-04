#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QCloseEvent>

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
    void write_settings();
    void read_settings();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

public slots:
    void bookmark();
    void pick_library_directory();
    void play_selected_book(QModelIndex idx);
    void set_position(int position);
    void update_position(qint64 position);
    void update_duration(qint64 duration);
    void update_info();
    void create_shortcuts();
    void quit();
    void update_media_state();
    void update_media_info();
    void set_playing_book(const QString &book_directory);
    void set_playing_chapter();
    void update_playback_mode();

};

#endif // MAINWINDOW_H



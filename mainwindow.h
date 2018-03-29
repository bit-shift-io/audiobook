#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AudioPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AudioPlayer *audio_player;
    //Playlist *playlist;

private:
    Ui::MainWindow *ui;

public slots:
    void play_pause();
    void bookmark();
    void open_file();

signals:
    void volume_changed();
};

#endif // MAINWINDOW_H



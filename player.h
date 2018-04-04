 
#ifndef PLAYER_H
#define PLAYER_H

#include "book.h"
#include <QMediaPlayer>

class Book;

class Player : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player(QMediaPlayer *parent = nullptr);
    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();
    uint playlist_time;
    float progress_scale;
    uint get_playlist_length();
    uint get_progress();
    const Book& get_playing_book();

protected:
    Book book;

public slots:
    void play_url(const QUrl& url);
    void set_playing_book(const Book &book);
    void set_playing_chapter(QString p_chapter);
    void seek_forward();
    void seek_backward();
    void increase_volume();
    void decrease_volume();
    void toggle_play_pause();
    void toggle_repeat();


};

#endif // AUDIOPLAYER_H

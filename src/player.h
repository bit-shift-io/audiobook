 
#ifndef PLAYER_H
#define PLAYER_H

#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    uint get_position();
    const Book& get_playing_book();
    const int get_playing_chapter_index();
    const QString get_playing_chapter_title();

protected:
    Book book;

public slots:
    void play_url(const QUrl& url);
    void set_playing_book(const Book &book);
    void set_playing_chapter(QString p_chapter);
    void set_position(uint p_position);
    void seek_forward();
    void seek_backward();
    void increase_volume();
    void decrease_volume();
    void set_playback_mode(QMediaPlaylist::PlaybackMode mode);
    void toggle_play_pause();
    void currentIndexChanged();


signals:
    void current_index_changed();

};

#endif // AUDIOPLAYER_H

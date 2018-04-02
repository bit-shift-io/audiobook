 
#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>

class Book;

class Player : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player(QMediaPlayer *parent = nullptr);
    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

public slots:
    void play_url(const QUrl& url);
    void play_book(const Book &book);
    void seek_forward();
    void seek_backward();
    void increase_volume();
    void decrease_volume();

signals:
    void duration_changed();
    void position_changed();
    void data_changed();

};

#endif // AUDIOPLAYER_H

 
#include "player.h"
#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

Player::Player(QMediaPlayer *parent) : QMediaPlayer(parent) {

}

QStringList Player::supportedMimeTypes() {
    QStringList result = QMediaPlayer::supportedMimeTypes();
    if (result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

void Player::play_book(const Book &book) {
    playlist_time = book.time;
    progress_scale = 100.0/playlist_time;

    QMediaPlaylist *playlist = new QMediaPlaylist;
    for(auto file_name: book.files)
    {
        QUrl url = QUrl::fromLocalFile(file_name);
        playlist->addMedia(url);
    }
    playlist->setCurrentIndex(1);
    setPlaylist(playlist);

    play();
}

void Player::play_url(const QUrl &url) {
    setMedia(url);
    play();
}

void Player::toggle_play_pause() {
    if (state() == QMediaPlayer::PausedState)
        play();
    else
        pause();
}

uint Player::get_playlist_length() {
    return playlist_time;
}

uint Player::get_progress() {
    return progress_scale * position();
}

void Player::seek_forward() {
}

void Player::seek_backward() {
}

void Player::increase_volume() {

}

void Player::decrease_volume() {

}


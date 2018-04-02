 
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


void Player::seek_forward() {
}

void Player::seek_backward() {
}

void Player::increase_volume() {

}

void Player::decrease_volume() {

}


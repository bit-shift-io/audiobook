 
#include "player.h"
#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

Player::Player(QMediaPlayer *parent) : QMediaPlayer(parent) {

}

void Player::playbackModeChanged() {
    emit playback_mode_changed();
}

void Player::currentIndexChanged() {
    emit current_index_changed();
}

QStringList Player::supportedMimeTypes() {
    QStringList result = QMediaPlayer::supportedMimeTypes();
    if (result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

void Player::set_playing_book(const Book &p_book) {
    book = p_book;
    playlist_time = book.time;
    progress_scale = 10000.0/playlist_time;

    QMediaPlaylist *playlist = new QMediaPlaylist;
    for(auto file_name: book.chapter_files)
    {
        QUrl url = QUrl::fromLocalFile(file_name);
        playlist->addMedia(url);
    }
    playlist->setCurrentIndex(1);
    setPlaylist(playlist);

    // connect this playlist to our slots
    connect(playlist, &QMediaPlaylist::playbackModeChanged, this, &Player::playbackModeChanged);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::currentIndexChanged);
}

void Player::set_playing_chapter(QString p_chapter) {
    int i = book.chapter_titles.indexOf(p_chapter);
    playlist()->setCurrentIndex(i);
}


const Book& Player::get_playing_book() {
    return book;
}

void Player::play_url(const QUrl &url) {
    setMedia(url);
    play();
}

void Player::toggle_play_pause() {
    if (state() != QMediaPlayer::PlayingState)
        play();
    else
        pause();
}

void Player::toggle_repeat() {
    if (playlist()->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential)
        playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
    else
        playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

uint Player::get_playlist_length() {
    return playlist_time;
}

uint Player::get_progress() {
    return progress_scale * get_position();
}

uint Player::get_position() {
    // account for chapters before current chapter
    int start_pos = 0;
    int idx = playlist()->currentIndex();
    for(int i = 0; i < idx ; ++i) {
        start_pos += book.chapter_times[i];
    }
    return start_pos + position();
}

void Player::seek_forward() {
}

void Player::seek_backward() {
}

void Player::increase_volume() {

}

void Player::decrease_volume() {

}


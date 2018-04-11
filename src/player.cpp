 
#include "player.h"

Player::Player(QMediaPlayer *parent) : QMediaPlayer(parent) {
    QMediaPlaylist *playlist = new QMediaPlaylist;
    setPlaylist(playlist);

    // connect this playlist to our slots
    //connect(playlist, &QMediaPlaylist::playbackModeChanged, this, &Player::playbackModeChanged);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::currentIndexChanged);
}

/*
void Player::playbackModeChanged() {
    emit playback_mode_changed();
}
*/
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

    playlist()->clear();

    for(auto file_name: book.chapter_files)
    {
        QUrl url = QUrl::fromLocalFile(file_name);
        playlist()->addMedia(url);
    }

    playlist()->setCurrentIndex(0);
}

void Player::set_playing_chapter(QString p_chapter) {
    int i = book.chapter_titles.indexOf(p_chapter);
    playlist()->setCurrentIndex(i);
}


const Book& Player::get_playing_book() {
    return book;
}

const int Player::get_playing_chapter_index() {
    return playlist()->currentIndex();
}

const QString Player::get_playing_chapter_title() {
    if (get_playing_chapter_index() == -1)
        return "";
    else
        return book.chapter_titles[get_playing_chapter_index()];
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

void Player::set_playback_mode(QMediaPlaylist::PlaybackMode mode) {
    playlist()->setPlaybackMode(mode);
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

void Player::set_position(uint p_position) {
    int idx = 0;

    // loop over chapters, reduce position by each chapter length till we are in the correct chapter
    for(int i = 0; i < book.chapter_times.length(); ++i) {
        if (p_position < book.chapter_times[i]) {
            idx = i;
            break;
        }
        p_position -= book.chapter_times[i];
    }

    // set chapter and position
    if (idx != playlist()->currentIndex())
        playlist()->setCurrentIndex(idx);
    //QMetaObject::invokeMethod(this, "setPosition", Qt::QueuedConnection, Q_ARG(qlonglong, p_position));
    setPosition(p_position);
}



void Player::seek_forward() {
    int current_position = get_position();
    current_position += 30000; // 30s
    set_position(current_position);
}

void Player::seek_backward() {
    int current_position = get_position();
    current_position -= 30000; // 30s
    if (current_position < 0)
        current_position = 0;
    set_position(current_position);
}

void Player::increase_volume() {
    setVolume(volume() + 10);
}

void Player::decrease_volume() {
    setVolume(volume() - 10);
}


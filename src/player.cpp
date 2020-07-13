#include "player.h"
#include "library.h"

Player::Player(QMediaPlayer *parent)
    : QMediaPlayer(parent)
{
    QMediaPlaylist *playlist = new QMediaPlaylist;
    setPlaylist(playlist);

    // connect this playlist to our slots
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::superCurrentIndexChanged);

    // connect library
    connect(Library::instance(), &Library::activeItemChanged, this, &Player::libraryItemChanged);
}


void Player::superCurrentIndexChanged() {
    emit currentIndexChanged();
}

void Player::libraryItemChanged()
{
    const Book* book = Library::instance()->getActiveItem();
    if (book != nullptr)
        setPlayingBook(*book); // cannot be null at this point, so use ref
}


Player *Player::instance()
{
    static Player* instance = new Player;
    return instance;
}


QObject *Player::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return Player::instance(); // C++ and QML instance
}


QStringList Player::supportedMimeTypes() {
    QStringList result = QMediaPlayer::supportedMimeTypes();
    if (result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

void Player::setPlayingBook(const Book &p_book) {
    book = p_book;
    mPlayListTime = book.time;
    mProgressScale = 10000.0/mPlayListTime;

    playlist()->clear();

    for(auto file_name: book.chapter_files)
    {
        QUrl url = QUrl::fromLocalFile(file_name);
        playlist()->addMedia(url);
    }

    playlist()->setCurrentIndex(0);
}

void Player::setPlayingChapter(QString p_chapter) {
    int i = book.chapter_titles.indexOf(p_chapter);
    playlist()->setCurrentIndex(i);
}


const Book& Player::getPlayingItem() {
    return book;
}

int Player::getPlayingChapterIndex() {
    return playlist()->currentIndex();
}

const QString Player::getPlayingChapterTitle() {
    if (getPlayingChapterIndex() == -1)
        return "";
    else
        return book.chapter_titles[getPlayingChapterIndex()];
}

void Player::playUrl(const QUrl &url) {
    setMedia(url);
    play();
}

void Player::setPlayingBook(int xLibraryIndex)
{
    /*
    const Book& book = Library::instance()->getLibraryItems().at(idx.row());
    setPlayingBook(book);
    play();
    */
}

void Player::togglePlayPause() {
    if (state() != QMediaPlayer::PlayingState)
        play();
    else
        pause();
}

void Player::setPlaybackMode(QMediaPlaylist::PlaybackMode mode) {
    playlist()->setPlaybackMode(mode);
}

uint Player::getPlaylistLength() {
    return mPlayListTime;
}

uint Player::getProgress() {
    return mProgressScale * getPosition();
}

uint Player::getPosition() {
    // account for chapters before current chapter
    int start_pos = 0;
    int idx = playlist()->currentIndex();
    for(int i = 0; i < idx ; ++i) {
        start_pos += book.chapter_times[i];
    }
    return start_pos + position();
}

void Player::setPosition(uint p_position) {
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



void Player::skipForward() {
    int current_position = getPosition();
    current_position += 30000; // 30s
    setPosition(current_position);
}

void Player::skipBackward() {
    int current_position = getPosition();
    current_position -= 30000; // 30s
    if (current_position < 0)
        current_position = 0;
    setPosition(current_position);
}

void Player::volumeUp() {
    setVolume(volume() + 10);
}

void Player::volumeDown() {
    setVolume(volume() - 10);
}


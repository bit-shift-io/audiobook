#include "player.h"
#include "library.h"
#include "util.h"

Player::Player(QMediaPlayer *parent)
    : QMediaPlayer(parent)
{
    // TODO: use parent playlist? parent->playlist()
    QMediaPlaylist *playlist = new QMediaPlaylist;
    setPlaylist(playlist);

    // connects
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::playlistIndexChanged);
    connect(this, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    connect(this, &QMediaPlayer::volumeChanged, this, &Player::volumeChanged);
    connect(this, &QMediaPlayer::playbackRateChanged, this, &Player::speedChanged);
    //connect(this, &QMediaPlayer::stateChanged, this, &Player::stateChanged);

    // connect library
    connect(Library::instance(), &Library::currentItemChanged, this, &Player::libraryItemChanged);
}


void Player::libraryItemChanged()
{
    const Book* book = Library::instance()->getCurrentItem();
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


void Player::setPlayingBook(const Book &xBook) {
    mBook = xBook;
    mPlayListTime = mBook.duration;
    mProgressScale = 10000.0/mPlayListTime;
    mProgress = 0;

    playlist()->clear();

    QString lib_path = Library::instance()->path();
    for(auto chapter: mBook.chapters)
    {
        QUrl url = QUrl::fromLocalFile(lib_path + chapter.path);
        playlist()->addMedia(url);
    }

    playlist()->setCurrentIndex(0);
    emit playlistChanged();
}


void Player::setChapterIndex(int xIndex) {
    playlist()->setCurrentIndex(xIndex);
}


QString Player::chapterText() const {
    if (playlist()->currentIndex() == -1)
        return "";

    return mBook.chapters[playlist()->currentIndex()].title;
}


QString Player::chapterProgressText() const
{
    if (playlist()->currentIndex() == -1)
        return "";

    QString index = QString::number(playlist()->currentIndex() +1);
    QString total = QString::number(playlist()->mediaCount());
    return QString("Chapter %1/%2").arg(index, total);
}


int Player::chapterIndex() const
{
    return playlist()->currentIndex();
}

int Player::volume() const
{
    return QMediaPlayer::volume();
}

qreal Player::speed() const
{
    return QMediaPlayer::playbackRate();
}


void Player::positionChanged(qint64 xPosition)
{
    // parent position has changed
    // account for chapters before current chapter
    qint64 start_pos = 0;
    int idx = playlist()->currentIndex();
    for(int i = 0; i < idx ; ++i) {
        start_pos += mBook.chapters[i].duration;
    }
    mProgress = start_pos + xPosition;
    emit progressChanged();
}


void Player::playlistIndexChanged(int xIndex)
{
    // pass from playlist to signal
    emit currentIndexChanged(xIndex);
}


void Player::togglePlayPause() {
    if (state() != QMediaPlayer::PlayingState) {
        QMediaPlayer::play();
    } else {
        QMediaPlayer::pause();
    }
}


void Player::setPlaybackMode(QMediaPlaylist::PlaybackMode mode) {
    playlist()->setPlaybackMode(mode);
}


qint64 Player::progress() const {
    // multiply by scale of the slider
    return mProgress * mProgressScale;
}


void Player::setProgress(qint64 xPosition)
{
    // convert from slider pos to playlisttime
    qint64 pos = mPlayListTime * xPosition / 10000.0;
    setHeadPosition(pos);
}


QString Player::positionText() const
{
    return Util::getDisplayTime(mProgress);
}


QString Player::timeText() const
{
    return Util::getDisplayTime(mPlayListTime);
}


QString Player::titleText() const
{
    return mBook.title;
}


void Player::setHeadPosition(qint64 xPosition) {
    // a wrapper for qmediaplayer::setPosition()
    int idx = 0;

    // loop over chapters, reduce position by each chapter length till we are in the correct chapter
    for(int i = 0; i < mBook.chapters.length(); ++i) {
        if (xPosition < mBook.chapters[i].duration) {
            idx = i;
            break;
        }
        xPosition -= mBook.chapters[i].duration;
    }

    // set chapter and position
    if (idx != playlist()->currentIndex())
        playlist()->setCurrentIndex(idx);

    setPosition(xPosition);
}



void Player::skipForward() {
    qint64 current_position = mProgress + mSkip;
    //if (current_position >= mPlayListTime) // TODO: check skip end of book
    setHeadPosition(current_position);
}

void Player::skipBackward() {
    qint64 current_position = mProgress - mSkip;
    if (current_position < 0)
        current_position = 0;
    setHeadPosition(current_position);
}

void Player::volumeUp() {
    setVolume(volume() + 25);
}

void Player::volumeDown() {
    setVolume(volume() - 25);
}

void Player::setVolume(int xVolume)
{
    QMediaPlayer::setVolume(xVolume);
}

void Player::setSpeed(qreal xSpeed)
{
    QMediaPlayer::setPlaybackRate(xSpeed);
}


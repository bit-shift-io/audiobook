
#include <QApplication>
#include "player.h"
#include "database.h"
#include "util.h"
#include "database.h"
#include "settings.h"

Player::Player(QMediaPlayer *parent)
    : QMediaPlayer(parent)
{
    // TODO: use parent playlist? parent->playlist()
    QMediaPlaylist *playlist = new QMediaPlaylist;
    setPlaylist(playlist);

    // load settings
    QString current_item = Settings::value("current_item", "").toString();
    setCurrentItem(current_item);

    // connects
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::playlistIndexChanged);
    connect(this, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    connect(this, &QMediaPlayer::volumeChanged, this, &Player::volumeChanged);
    connect(this, &QMediaPlayer::playbackRateChanged, this, &Player::speedChanged);
    //connect(this, &QMediaPlayer::stateChanged, this, &Player::stateChanged);

    // exit app
    connect(qApp, &QApplication::aboutToQuit, this, &Player::exitHandler);
}


Player::~Player()
{
    mCurrentBook = nullptr;
    delete mCurrentBook;
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


void Player::loadBook() {
    mProgressScale = 10000.0/mCurrentBook->duration;

    playlist()->clear();

    QString lib_path = Database::instance()->libraryPath();
    for(auto chapter: mCurrentBook->chapters)
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

    return mCurrentBook->chapters[playlist()->currentIndex()].title;
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


void Player::exitHandler()
{
}


void Player::positionChanged(qint64 xPosition)
{
    // parent position has changed
    // account for chapters before current chapter
    qint64 start_pos = 0;
    int idx = playlist()->currentIndex();
    for(int i = 0; i < idx ; ++i) {
        start_pos += mCurrentBook->chapters[i].duration;
    }
    mCurrentBook->progress = start_pos + xPosition;
    Database::instance()->writeBook(*mCurrentBook);
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
    if (mCurrentBook == nullptr)
        return 0;

    // multiply by scale of the slider
    return mCurrentBook->progress * mProgressScale;
}


void Player::setProgress(qint64 xPosition)
{
    // convert from slider pos to playlisttime
    mCurrentBook->progress = mCurrentBook->duration * xPosition / 10000.0;
    setHeadPosition(mCurrentBook->progress);
}


QString Player::positionText() const
{
    if (mCurrentBook == nullptr)
        return QString();

    return Util::getDisplayTime(mCurrentBook->progress);
}


QString Player::timeText() const
{
    if (mCurrentBook == nullptr)
        return QString();

    return Util::getDisplayTime(mCurrentBook->duration);
}


QString Player::titleText() const
{
    if (mCurrentBook == nullptr)
        return QString();

    return mCurrentBook->title;
}


void Player::setHeadPosition(qint64 xPosition) {
    // a wrapper for qmediaplayer::setPosition()
    int idx = 0;

    // loop over chapters, reduce position by each chapter length till we are in the correct chapter
    for(int i = 0; i < mCurrentBook->chapters.length(); ++i) {
        if (xPosition < mCurrentBook->chapters[i].duration) {
            idx = i;
            break;
        }
        xPosition -= mCurrentBook->chapters[i].duration;
    }

    // set chapter and position
    if (idx != playlist()->currentIndex())
        playlist()->setCurrentIndex(idx);

    // TODO: when the user click the timeline, we need to setPosition(),
    // if its changing between chapters, we
    // then wait for the signal QMediaPlayer::currentMediaChanged
    // then apply the new position
    QMediaPlayer::setPosition(xPosition);
}



void Player::skipForward() {
    qint64 current_position = mCurrentBook->progress + mSkip;
    //if (current_position >= mPlayListTime) // TODO: check skip end of book
    setHeadPosition(current_position);
}

void Player::skipBackward() {
    qint64 current_position = mCurrentBook->progress - mSkip;
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


void Player::setCurrentItem(QString &xIndex)
{
    if (xIndex.isEmpty())
        return;

    if (mCurrentBook != nullptr && mCurrentBook->path == xIndex)
        return;

    mCurrentBook = Database::instance()->getLibraryItem(xIndex);
    Settings::setValue("current_item", xIndex);
    loadBook();
    setHeadPosition(mCurrentBook->progress);
}


QString Player::currentItem()
{
    return mCurrentBook->path;
}


Book * Player::getCurrentItem()
{
    return mCurrentBook;
}



#include <QApplication>
#include <QSettings>
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
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::playlistIndexChanged);

    connect(this, &QMediaPlayer::mediaStatusChanged, this, &Player::updateMediaStatus);
    connect(this, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
    connect(this, &QMediaPlayer::volumeChanged, this, &Player::volumeChanged);
    connect(this, &QMediaPlayer::playbackRateChanged, this, &Player::speedChanged);

    connect(this, &QMediaPlayer::seekableChanged, this, &Player::updateSeekable); // broken on android
    connect(this, &QMediaPlayer::bufferStatusChanged, this, &Player::updateBuffer); // broken on desktop??

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &Player::endSleepTimer);

    // exit app
    connect(qApp, &QApplication::aboutToQuit, this, &Player::exitHandler);

    // load settings
    QString current_item = Settings::value("current_item", "").toString();
    setCurrentItem(current_item);

    int volume = Settings::value("volume", 100).toInt();
    setVolume(volume);

    int speed = Settings::value("speed", 100).toInt();
    setSpeed(speed);

    int sleep_time = Settings::value("sleep_time", 3600000).toInt(); // 1hr in msec
    setSleepTime(sleep_time);

    Repeat repeat_mode = static_cast<Repeat>(Settings::value("repeat_mode", Repeat::LIBRARY).toInt());
    setRepeatMode(repeat_mode);
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


void Player::setChapterIndex(int xIndex) {
    // disable progress update while changing chapter
    disconnect(this, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
    QMediaPlayer::setMuted(true);
    playlist()->setCurrentIndex(xIndex);
}


QString Player::chapterText() const {
    if (playlist()->currentIndex() == -1)
        return "";

    return mCurrentBook->chapters[playlist()->currentIndex()].title;
}


QString Player::chapterProgressText() const
{
    if (chapterIndex() == -1)
        return "";

    QString index = QString::number(playlist()->currentIndex() +1);
    QString total = QString::number(playlist()->mediaCount());
    return QString("Chapter %1/%2").arg(index, total);
}


QString Player::sleepTimeText() const
{
    return Util::getDisplayTime(mSleepTime);
}


QString Player::repeatModeText() const
{
    QString result = QMetaEnum::fromType<Player::Repeat>().valueToKey(mRepeatMode);
    result = result.toLower();
    result[0] = result.at(0).toTitleCase();
    return result;
}


Player::Repeat Player::repeatMode() const
{
    return mRepeatMode;
}


int Player::chapterIndex() const
{
    return playlist()->currentIndex();
}


int Player::volume() const
{
    return QMediaPlayer::volume();
}


int Player::speed() const
{
    return QMediaPlayer::playbackRate() * 100;
}


int Player::sleepTime() const
{
    return mSleepTime;
}


bool Player::sleepTimerEnabled() const
{
    return mSleepTimeEnabled;
}


void Player::endSleepTimer()
{
   QMediaPlayer::pause();
   setSleepTimerEnabled(false);
}


void Player::exitHandler()
{
    Database::instance()->writeBook(*mCurrentBook);
}


void Player::playlistIndexChanged(int xIndex)
{
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


qint64 Player::sliderValue() const {
    // multiply by scale of the slider
    return mProgress * mProgressScale;
}


void Player::setSliderValue(qint64 xPosition)
{
    // this should only be called from qml
    // this converts the slider value to progress
    // convert from slider pos to playlisttime(progress)
    qint64 p = mCurrentBook->duration * xPosition / 10000.0;
    setProgress(p);
}


QString Player::positionText() const
{
    if (mCurrentBook == nullptr)
        return QString();

    return Util::getDisplayTime(mProgress);
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


void Player::updatePosition(qint64 xPosition)
{
    mProgress = mCurrentBook->getStartProgressChapter(chapterIndex()) + xPosition;
    mCurrentBook->progress = mProgress;
    emit progressChanged();
}


void Player::setProgress(qint64 xPosition) {
    // this converts from book progress to
    // chapter index
    // chapter time -> position
    int chapter_index = mCurrentBook->getChapterIndex(xPosition);
    qint64 chapter_position = mCurrentBook->getChapterPosition(xPosition);

    if (chapter_index == chapterIndex()) {
        QMediaPlayer::setPosition(chapter_position);
        return;
    }

    // set chapter and position
    mSetPosition = chapter_position;
    setChapterIndex(chapter_index);
}


void Player::skipForward() {
    qint64 current_position = mProgress + mSkip;
    if (current_position >= mCurrentBook->duration)
        current_position = mCurrentBook->duration - 1;
    setProgress(current_position);
}


void Player::skipBackward() {
    qint64 current_position = mProgress - mSkip;
    if (current_position < 0)
        current_position = 0;
    setProgress(current_position);
}


void Player::volumeUp() {
    setVolume(volume() + 25);
}


void Player::volumeDown() {
    setVolume(volume() - 25);
}


void Player::setVolume(int xVolume)
{
    if (QMediaPlayer::volume() == xVolume)
        return;

    QMediaPlayer::setMuted(false);
    QMediaPlayer::setVolume(xVolume);
    Settings::setValue("volume", xVolume);
}


void Player::setSpeed(int xSpeed)
{
    if ((QMediaPlayer::playbackRate() * 100) == xSpeed)
        return;

    QMediaPlayer::setPlaybackRate(xSpeed/100.0);
    Settings::setValue("speed", xSpeed);
}


void Player::setSleepTime(int xTime)
{
    if (mSleepTime == xTime)
        return;

    mSleepTime = xTime;
    Settings::setValue("sleep_time", mSleepTime);
    emit sleepTimeChanged(mSleepTime);
}


void Player::setSleepTimerEnabled(bool xEnabled)
{
    if (mSleepTimeEnabled == xEnabled)
        return;

    mSleepTimeEnabled = xEnabled;

    if (mSleepTimeEnabled)
        mTimer->start(mSleepTime);
    else
        mTimer->stop();

    emit sleepTimerEnabledChanged(mSleepTimeEnabled);
}


void Player::updateMediaStatus(QMediaPlayer::MediaStatus xStatus)
{
    if (xStatus == QMediaPlayer::NoMedia && chapterIndex() == -1 && mRepeatMode == Repeat::LIBRARY && !mChangingBook) {
        QString next_book = Database::instance()->getNextLibraryItem(mCurrentBook->path)->path;
        setCurrentItem(next_book);
    }
}


void Player::updateSeekable(bool xSeekable)
{
    if (xSeekable) {
        // completed loading chapter
        connect(this, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
        QMediaPlayer::setPosition(mSetPosition);
        setMuted(false);
        mSetPosition = -1;
        mChangingBook = false;
    }
}


void Player::updateBuffer(int xValue)
{
    if (xValue == 100)
        updateSeekable(QMediaPlayer::isSeekable());
}


void Player::setRepeatMode(Player::Repeat xMode)
{
    if (mRepeatMode == xMode)
        return;

    mRepeatMode = xMode;
    Settings::setValue("repeat_mode", mRepeatMode);

    switch(mRepeatMode){
    case(Repeat::LIBRARY):
        playlist()->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    case(Repeat::BOOK):
        playlist()->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case(Repeat::CHAPTER):
        playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case(Repeat::NONE):
        playlist()->setPlaybackMode(QMediaPlaylist::Sequential);
        break;

    }

    emit repeatModeChanged(mRepeatMode);
}


void Player::setCurrentItem(QString &xIndex)
{
    if (xIndex.isEmpty())
        return;

    if (mCurrentBook != nullptr && mCurrentBook->path == xIndex)
        return;

    disconnect(this, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
    mChangingBook = true;


    if (mCurrentBook != nullptr) {
        // if near end of book, reset progress
        if (mCurrentBook->duration - mCurrentBook->progress < 10000 ) // 10 seconds
            mCurrentBook->progress = 0;

        // save book progress
        Database::instance()->writeBook(*mCurrentBook);
    }

    // load the new book to playlist
    playlist()->clear();
    Settings::setValue("current_item", xIndex);
    mCurrentBook = Database::instance()->getLibraryItem(xIndex);

    mSetPosition = -1;
    mProgressScale = 10000.0/mCurrentBook->duration;
    mProgress = mCurrentBook->progress;
    emit progressChanged();

    for(auto chapter: mCurrentBook->chapters)
    {
        QUrl url = QUrl::fromLocalFile(Database::instance()->libraryPath() + chapter.path);
        playlist()->addMedia(url);
    }

    // changing book requires this
    emit playlistChanged();

    // set a default item in the playlist
    //setChapterIndex(0);

    connect(this, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
    setProgress(mProgress);
}


QString Player::currentItem()
{
    return mCurrentBook->path;
}


Book * Player::getCurrentItem()
{
    return mCurrentBook;
}


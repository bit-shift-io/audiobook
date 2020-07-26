
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

    // connects
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::playlistIndexChanged);
    connect(this, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    connect(this, &QMediaPlayer::volumeChanged, this, &Player::volumeChanged);
    connect(this, &QMediaPlayer::playbackRateChanged, this, &Player::speedChanged);
    connect(this, &QMediaPlayer::seekableChanged, this, &Player::seekableChanged);

    // exit app
    connect(qApp, &QApplication::aboutToQuit, this, &Player::exitHandler);

    // load settings
    QString current_item = Settings::value("current_item", "").toString();
    setCurrentItem(current_item);
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
    mProgress = mCurrentBook->progress;

    playlist()->clear();
    for(auto chapter: mCurrentBook->chapters)
    {
        QUrl url = QUrl::fromLocalFile(Database::instance()->libraryPath() + chapter.path);
        playlist()->addMedia(url);
    }

    setProgress(mCurrentBook->progress);
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


void Player::seekableChanged(bool seekable)
{
    // when the audio is seekable
    // we can unmute, and progress the track head
    if (seekable && mSetPosition != -1) {
        setPosition(mSetPosition);
        setMuted(false);
        mSetPosition = -1;
    }
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


void Player::positionChanged(qint64 xPosition)
{
    // dont change progress if media is changing
    if (mSetPosition > xPosition) {
        //setProgress(mSetPosition);
        return;
    }

    mProgress = mCurrentBook->getStartProgressChapter(chapterIndex()) + xPosition;
    mCurrentBook->progress = mProgress;
    Database::instance()->writeBook(*mCurrentBook);
    emit progressChanged();
}


void Player::setProgress(qint64 xPosition) {
    // this converts from book progress to
    // chapter index
    // chapter time -> position
    int chapter_index = 0;
    qint64 chapter_position = xPosition;

    // loop over chapters, reduce position by each chapter length till we are in the correct chapter
    for(int i = 0; i < mCurrentBook->chapters.length(); ++i) {
        if (chapter_position < mCurrentBook->chapters[i].duration) {
            chapter_index = i;
            break;
        }
        chapter_position -= mCurrentBook->chapters[i].duration;
    }

    if (chapter_index == chapterIndex()) {
        QMediaPlayer::setPosition(chapter_position);
        return;
    }

    // set chapter and position
    QMediaPlayer::setMuted(true);
    mSetPosition = chapter_position;
    setChapterIndex(chapter_index);
}


void Player::skipForward() {
    qint64 current_position = mProgress + mSkip;
    //if (current_position >= mPlayListTime) // TODO: check skip end of book
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
}


QString Player::currentItem()
{
    return mCurrentBook->path;
}


Book * Player::getCurrentItem()
{
    return mCurrentBook;
}


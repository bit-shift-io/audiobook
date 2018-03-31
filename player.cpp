 
#include "player.h"
#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

Player::Player(QObject *parent) : QObject(parent)
{
    /*
    createWidgets();
    createShortcuts();
    createJumpList();
    createTaskbar();
    createThumbnailToolBar();

    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioPlayer::updatePosition);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &AudioPlayer::updateDuration);
    connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &AudioPlayer::updateInfo);
*/
    typedef void(QMediaPlayer::*ErrorSignal)(QMediaPlayer::Error);
    /*
    connect(&mediaPlayer, static_cast<ErrorSignal>(&QMediaPlayer::error),
            this, &AudioPlayer::handleError);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged,
            this, &AudioPlayer::updateState);

    stylize();
    //setAcceptDrops(true);
    */
}

QStringList Player::supportedMimeTypes()
{
    QStringList result = QMediaPlayer::supportedMimeTypes();
    if (result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

void Player::play_book(const Book &book)
{
    QMediaPlaylist *playlist = new QMediaPlaylist;
    QUrl url = QUrl::fromLocalFile(book.files.at(0));
    playlist->addMedia(url);
    playlist->setCurrentIndex(1);
    mediaPlayer.setPlaylist(playlist);
    mediaPlayer.play();
}

void Player::play_url(const QUrl &url)
{
     /* - move to ui
    playButton->setEnabled(true);

    if (url.isLocalFile()) {
        const QString filePath = url.toLocalFile();
        setWindowFilePath(filePath);
        infoLabel->setText(QDir::toNativeSeparators(filePath));
        fileName = QFileInfo(filePath).fileName();
    } else {
        setWindowFilePath(QString());
        infoLabel->setText(url.toString());
        fileName.clear();
    }
    */

    mediaPlayer.setMedia(url);
    mediaPlayer.play();
}


void Player::toggle_play_pause()
{
    if (mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
        int i = 0;
        //openFile();
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

#if 0
void AudioPlayer::seekForward()
{
    //positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void AudioPlayer::seekBackward()
{
    //positionSlider->triggerAction(QSlider::SliderPageStepSub);
}
#endif

bool Player::event(QEvent *event)
{
    /*
    if (event->type() == QWinEvent::CompositionChange || event->type() == QWinEvent::ColorizationChange)
        stylize();
        */
    return QObject::event(event);
}

#if 0
static bool canHandleDrop(const QDropEvent *event)
{
        /*
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.size() != 1)
        return false;
    QMimeDatabase mimeDatabase;
    return AudioPlayer::supportedMimeTypes().
        contains(mimeDatabase.mimeTypeForUrl(urls.constFirst()).name());
        */
}


void AudioPlayer::dragEnterEvent(QDragEnterEvent *event)
{
    event->setAccepted(canHandleDrop(event));
}

void AudioPlayer::dropEvent(QDropEvent *event)
{
    event->accept();
    playUrl(event->mimeData()->urls().constFirst());
}

void AudioPlayer::mousePressEvent(QMouseEvent *event)
{
    offset = event->globalPos() - pos();
    event->accept();
}

void AudioPlayer::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset);
    event->accept();
}

void AudioPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    offset = QPoint();
    event->accept();
}

void AudioPlayer::stylize()
{
    /*
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);
        setStyleSheet(QStringLiteral("MusicPlayer { background: transparent; }"));
    } else {
        QtWin::resetExtendedFrame(this);
        setAttribute(Qt::WA_TranslucentBackground, false);
        setStyleSheet(QStringLiteral("MusicPlayer { background: %1; }").arg(QtWin::realColorizationColor().name()));
    }
    */
    volumeButton->stylize();
}


void AudioPlayer::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        playButton->setToolTip(tr("Pause"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        playButton->setToolTip(tr("Play"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

static QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void AudioPlayer::updatePosition(qint64 position)
{
    positionSlider->setValue(position);
    positionLabel->setText(formatTime(position));
}

void AudioPlayer::updateDuration(qint64 duration)
{
    positionSlider->setRange(0, duration);
    positionSlider->setEnabled(duration > 0);
    positionSlider->setPageStep(duration / 10);
    updateInfo();
}
#endif
void Player::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(mediaPlayer.position() - position) > 99)
        mediaPlayer.setPosition(position);
}

#if 0
void AudioPlayer::updateInfo()
{
    QStringList info;
    if (!fileName.isEmpty())
        info.append(fileName);
    if (mediaPlayer.isMetaDataAvailable()) {
        QString author = mediaPlayer.metaData(QStringLiteral("Author")).toString();
        if (!author.isEmpty())
            info.append(author);
        QString title = mediaPlayer.metaData(QStringLiteral("Title")).toString();
        if (!title.isEmpty())
            info.append(title);
    }
    info.append(formatTime(mediaPlayer.duration()));
    infoLabel->setText(info.join(tr(" - ")));
}


void AudioPlayer::handleError()
{
    playButton->setEnabled(false);
    const QString errorString = mediaPlayer.errorString();
    infoLabel->setText(errorString.isEmpty()
                       ? tr("Unknown error #%1").arg(int(mediaPlayer.error()))
                       : tr("Error: %1").arg(errorString));
}

void AudioPlayer::updateTaskbar()
{
    /*
    switch (mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        taskbarProgress->show();
        taskbarProgress->resume();
        break;
    case QMediaPlayer::PausedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPause));
        taskbarProgress->show();
        taskbarProgress->pause();
        break;
    case QMediaPlayer::StoppedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaStop));
        taskbarProgress->hide();
        break;
    }
    */
}

void AudioPlayer::updateThumbnailToolBar()
{
    /*
    playToolButton->setEnabled(mediaPlayer.duration() > 0);
    backwardToolButton->setEnabled(mediaPlayer.position() > 0);
    forwardToolButton->setEnabled(mediaPlayer.position() < mediaPlayer.duration());

    if (mediaPlayer.state() == QMediaPlayer::PlayingState) {
        playToolButton->setToolTip(tr("Pause"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        playToolButton->setToolTip(tr("Play"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    */
}

void AudioPlayer::createWidgets()
{
    bookmarkButton = new QToolButton(this);
    bookmarkButton->setEnabled(false);
    bookmarkButton->setToolTip(tr("Bookmark"));
    bookmarkButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(bookmarkButton, &QAbstractButton::clicked, this, &AudioPlayer::togglePlayback);

    playButton = new QToolButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &AudioPlayer::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &AudioPlayer::openFile);

    volumeButton = new VolumeButton(this);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(mediaPlayer.volume());
    connect(volumeButton, &VolumeButton::volumeChanged, &mediaPlayer, &QMediaPlayer::setVolume);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
    connect(positionSlider, &QAbstractSlider::valueChanged, this, &AudioPlayer::setPosition);

    infoLabel = new QLabel(this);
    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(bookmarkButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(volumeButton);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(controlLayout);
}

void AudioPlayer::createShortcuts()
{
    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, this);
    connect(quitShortcut, &QShortcut::activated, QCoreApplication::quit);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &AudioPlayer::openFile);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &AudioPlayer::togglePlayback);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &AudioPlayer::seekForward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &AudioPlayer::seekBackward);

    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
    connect(increaseShortcut, &QShortcut::activated, volumeButton, &VolumeButton::increaseVolume);

    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
    connect(decreaseShortcut, &QShortcut::activated, volumeButton, &VolumeButton::descreaseVolume);
}

void AudioPlayer::createJumpList()
{
    /*
    QWinJumpList jumplist;
    jumplist.recent()->setVisible(true);
    */
}

void AudioPlayer::createTaskbar()
{
    /*
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());

    taskbarProgress = taskbarButton->progress();
    connect(positionSlider, &QAbstractSlider::valueChanged, taskbarProgress, &QWinTaskbarProgress::setValue);
    connect(positionSlider, &QAbstractSlider::rangeChanged, taskbarProgress, &QWinTaskbarProgress::setRange);

    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayer::updateTaskbar);
    */
}

void AudioPlayer::createThumbnailToolBar()
{
    /*
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    thumbnailToolBar->setWindow(windowHandle());

    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    playToolButton->setEnabled(false);
    playToolButton->setToolTip(tr("Play"));
    playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::togglePlayback);

    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    forwardToolButton->setEnabled(false);
    forwardToolButton->setToolTip(tr("Fast forward"));
    forwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    connect(forwardToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::seekForward);

    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    backwardToolButton->setEnabled(false);
    backwardToolButton->setToolTip(tr("Rewind"));
    backwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(backwardToolButton, &QWinThumbnailToolButton::clicked, this, &MusicPlayer::seekBackward);

    thumbnailToolBar->addButton(backwardToolButton);
    thumbnailToolBar->addButton(playToolButton);
    thumbnailToolBar->addButton(forwardToolButton);

    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::updateThumbnailToolBar);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateThumbnailToolBar);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayer::updateThumbnailToolBar);
    */
}
#endif

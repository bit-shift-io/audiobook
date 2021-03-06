 #ifndef PLAYER_H
#define PLAYER_H

#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class QTimer;
class Book;
class QQmlEngine;
class QJSEngine;

class Player : public QMediaPlayer
{
    Q_OBJECT

    Q_PROPERTY(QString currentItem WRITE setCurrentItem NOTIFY currentItemChanged)
    Q_PROPERTY(qint64 sliderValue READ sliderValue NOTIFY progressChanged)
    Q_PROPERTY(int chapterIndex READ chapterIndex WRITE setChapterIndex NOTIFY progressChanged)
    Q_PROPERTY(QString positionText READ positionText NOTIFY progressChanged)
    Q_PROPERTY(QString timeText READ timeText NOTIFY playlistChanged)
    Q_PROPERTY(QString titleText READ titleText NOTIFY playlistChanged)
    Q_PROPERTY(QString chapterText READ chapterText NOTIFY currentIndexChanged)
    Q_PROPERTY(QString chapterProgressText READ chapterProgressText NOTIFY currentIndexChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int sleepTime READ sleepTime WRITE setSleepTime NOTIFY sleepTimeChanged)
    Q_PROPERTY(QString sleepTimeText READ sleepTimeText NOTIFY sleepTimeChanged)
    Q_PROPERTY(bool sleepTimerEnabled READ sleepTimerEnabled WRITE setSleepTimerEnabled NOTIFY sleepTimerEnabledChanged)
    Q_PROPERTY(Player::Repeat repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged)
    Q_PROPERTY(QString repeatModeText READ repeatModeText NOTIFY repeatModeChanged)

public:
    enum Repeat {
        LIBRARY = 0,
        BOOK,
        CHAPTER,
        NONE,
    };
    Q_ENUM(Repeat);

    ~Player();
    Player(const Player&) = delete; // disable copy for singleton
    static Player *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    qint64 sliderValue() const;
    QString positionText() const;
    QString timeText() const;
    QString titleText() const;
    QString chapterText() const;
    QString chapterProgressText() const;
    QString sleepTimeText() const;
    QString repeatModeText() const;
    Player::Repeat repeatMode() const;
    int chapterIndex() const;
    int volume() const;
    int speed() const;
    int sleepTime() const;
    bool sleepTimerEnabled() const;
    void endSleepTimer();
    void exitHandler();

    // current/active item
    void setCurrentItem(QString &xIndex);
    QString currentItem();
    Book * getCurrentItem();

public slots:
    void setRepeatMode(Player::Repeat xMode);
    void updatePosition(qint64 xPosition);
    void playlistIndexChanged(int xIndex);
    void setProgress(qint64 xPosition);
    void setSliderValue(qint64 xPosition);
    void setChapterIndex(int xIndex);
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void togglePlayPause();
    void skipForward();
    void skipBackward();
    void volumeUp();
    void volumeDown();
    void setVolume(int xVolume);
    void setSpeed(int xSpeed);
    void setSleepTime(int xTime);
    void setSleepTimerEnabled(bool xEnabled);
    void updateMediaStatus(QMediaPlayer::MediaStatus xStatus);
    void updateSeekable(bool xSeekable);
    void updateBuffer(int xValue);

signals:
    void progressChanged();
    void playlistChanged();
    void currentIndexChanged(int xIndex);
    void volumeChanged(int xVolume);
    void speedChanged(int xSpeed);
    void sleepTimeChanged(int xTime);
    void sleepTimerEnabledChanged(bool xEnabled);
    void repeatModeChanged(enum Player::Repeat xMode);


private:
    enum Player::Repeat mRepeatMode;
    Book * mCurrentBook = nullptr;
    int mSkip = 30000; // 30 sec
    float mProgressScale; // decimal
    qint64 mSetPosition = -1;
    qint64 mProgress = 0;
    int mSleepTime = 3600000; // 1hr
    bool mSleepTimeEnabled = false;
    bool mChangingBook = false;
    QTimer * mTimer = nullptr;
    explicit Player(QMediaPlayer *parent = nullptr);
};

#endif // PLAYER_H

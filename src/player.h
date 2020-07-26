 #ifndef PLAYER_H
#define PLAYER_H

#include "book.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
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
    int chapterIndex() const;
    int volume() const;
    qreal speed() const;
    void exitHandler();
    void seekableChanged(bool seekable);

    // current/active item
    void setCurrentItem(QString &xIndex);
    QString currentItem();
    Book * getCurrentItem();

public slots:
    void positionChanged(qint64 xPosition);
    void playlistIndexChanged(int xIndex);
    void setProgress(qint64 xPosition);
    void setSliderValue(qint64 xPosition);
    void loadBook();
    void setChapterIndex(int xIndex);
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void togglePlayPause();
    void skipForward();
    void skipBackward();
    void volumeUp();
    void volumeDown();
    void setVolume(int xVolume);
    void setSpeed(qreal xSpeed);

signals:
    void progressChanged();
    void playlistChanged();
    void currentIndexChanged(int xIndex);
    void volumeChanged(int xVolume);
    void speedChanged(qreal xSpeed);


private:
    Book * mCurrentBook = nullptr;
    int mSkip = 30000; // 30 sec
    float mProgressScale; // decimal
    qint64 mSetPosition = -1;
    qint64 mProgress = 0;
    explicit Player(QMediaPlayer *parent = nullptr);
};

#endif // PLAYER_H

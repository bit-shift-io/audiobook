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
    //Q_PROPERTY(QString play READ play WRITE setPlay NOTIFY playChanged)
    Q_PROPERTY(qint64 progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QString positionText READ positionText NOTIFY progressChanged)
    Q_PROPERTY(QString timeText READ timeText NOTIFY playlistChanged)
    Q_PROPERTY(QString titleText READ titleText NOTIFY playlistChanged)
    Q_PROPERTY(QString chapterText READ chapterText NOTIFY playlistChanged)

public:
    Player(const Player&) = delete; // disable copy for singleton
    static Player *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    qint64 progress() const;
    QString positionText() const;
    QString timeText() const;
    QString titleText() const;
    QString chapterText() const;

public slots:
    void positionChanged(qint64 xPosition);
    void playlistIndexChanged(int xIndex);
    void libraryItemChanged();
    void setHeadPosition(qint64 xPosition);
    void setProgress(qint64 xPosition);
    void setPlayingBook(const Book &mBook);
    void setPlayingChapter(QString p_chapter);
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void togglePlayPause();
    void skipForward();
    void skipBackward();
    void volumeUp();
    void volumeDown();


signals:
    void progressChanged();
    void playlistChanged();


private:
    Book mBook;
    qint64 mProgress = 0;
    int mSkip = 30000; // 30 sec
    qint64 mPlayListTime = 0;
    float mProgressScale; // decimal
    explicit Player(QMediaPlayer *parent = nullptr);
};

#endif // PLAYER_H

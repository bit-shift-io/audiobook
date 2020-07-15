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

public:
    Player(const Player&) = delete; // disable copy for singleton
    static Player *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    qint64 progress() const;


    QString positionText() const;
    QString timeText() const;

    // old
    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();
    qint64 getPlaylistLength();
    const Book& getPlayingItem();
    int getPlayingChapterIndex();
    const QString getPlayingChapterTitle();

protected:


public slots:
    void positionChanged(qint64 xPosition);
    void libraryItemChanged();
    void setHeadPosition(qint64 xPosition);
    void setProgress(qint64 xPosition);

    // old
    void playUrl(const QUrl& url);
    void setPlayingBook(const Book &mBook);
    void setPlayingChapter(QString p_chapter);
    void skipForward();
    void skipBackward();
    void volumeUp();
    void volumeDown();
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void togglePlayPause();
    void superCurrentIndexChanged();


signals:
    void progressChanged();
    void playlistChanged();

    // old
    void currentIndexChanged();

private:
    Book mBook;
    qint64 mProgress = 0;
    int mSkip = 30000; // 30 sec
    qint64 mPlayListTime = 0;
    float mProgressScale; // decimal
    explicit Player(QMediaPlayer *parent = nullptr);

};

#endif // AUDIOPLAYER_H

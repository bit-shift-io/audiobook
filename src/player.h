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
    Q_PROPERTY(uint progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    Player(const Player&) = delete; // disable copy for singleton
    static Player *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

    uint progress() const;
    uint getPosition() const;
    void setProgress(qint64 xPosition);

    uint getPlaylistLength();

    const Book& getPlayingItem();
    int getPlayingChapterIndex();
    const QString getPlayingChapterTitle();

protected:
    Book book;

public slots:
    void positionChanged(qint64 xPosition);
    void libraryItemChanged();

    // old
    void playUrl(const QUrl& url);
    void setPlayingBook(const Book &book);
    void setPlayingChapter(QString p_chapter);
    void setPosition(uint p_position);
    void skipForward();
    void skipBackward();
    void volumeUp();
    void volumeDown();
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void togglePlayPause();
    void superCurrentIndexChanged();


signals:
    void currentIndexChanged();
    void progressChanged();

private:
    qint64 mProgress = 0;
    int mSkip = 30000; // 30 sec
    qint64 mPlayListTime;
    qint64 mProgressScale;
    explicit Player(QMediaPlayer *parent = nullptr);

};

#endif // AUDIOPLAYER_H

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
    Q_PROPERTY(QString play READ play WRITE setPlay NOTIFY playChanged)

public:
    Player(const Player&) = delete; // disable copy for singleton
    static Player *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

    uint getPlaylistLength();
    uint getProgress();
    uint getPosition();
    const Book& getPlayingItem();
    int getPlayingChapterIndex();
    const QString getPlayingChapterTitle();

protected:
    Book book;

public slots:
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
    //void currentIndexChanged();


signals:
    void currentIndexChanged();

private:
    uint mPlayListTime;
    float mProgressScale;
    explicit Player(QMediaPlayer *parent = nullptr);

};

#endif // AUDIOPLAYER_H

 
#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QPoint>


class Book;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

public slots:
    //void openFile();
    void play_url(const QUrl& url);
    void toggle_play_pause();
    void play_book(const Book &book);
    //void seekForward();
    //void seekBackward();

protected:
    bool event(QEvent *event) override;
    //void dragEnterEvent(QDragEnterEvent *event) override;
    //void dropEvent(QDropEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    //void stylize();
    //void updateState(QMediaPlayer::State state);
    //void updatePosition(qint64 position);
    //void updateDuration(qint64 duration);
    void setPosition(int position);
    //void updateInfo();
    //void handleError();

    //void updateTaskbar();
    //void updateThumbnailToolBar();

private:
    //void createWidgets();
    //void createShortcuts();
    //void createJumpList();
    //void createTaskbar();
    //void createThumbnailToolBar();

    //QWinTaskbarButton *taskbarButton = nullptr;
    //QWinTaskbarProgress *taskbarProgress = nullptr;
    //QWinThumbnailToolBar *thumbnailToolBar = nullptr;
    //QWinThumbnailToolButton *playToolButton = nullptr;
    //QWinThumbnailToolButton *forwardToolButton = nullptr;
    //QWinThumbnailToolButton *backwardToolButton = nullptr;

    QMediaPlayer mediaPlayer;
    //QAbstractButton *bookmarkButton = nullptr;
    //QAbstractButton *playButton = nullptr;
    //VolumeButton *volumeButton = nullptr;
    //QSlider *positionSlider = nullptr;
    //QLabel *positionLabel = nullptr;
    //QLabel *infoLabel = nullptr;
    QPoint offset;
    QString fileName;
};

#endif // AUDIOPLAYER_H

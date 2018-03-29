 
#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>

class VolumeButton;

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolBar)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolButton)

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);

    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

public slots:
    //void openFile();
    void playUrl(const QUrl& url);
    void togglePlayback();
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

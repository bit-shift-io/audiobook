
#include <QDebug>
#include <QKeySequence>
#include <QShortcut>
#include "shortcuts.h"
#include "shortcut.h"

Shortcuts::Shortcuts(QObject *parent)
    : QObject(parent)
{
    qApp->installEventFilter(this);
    init();
}


Shortcuts *Shortcuts::instance()
{
    static Shortcuts* instance = new Shortcuts;
    return instance;
}


QObject *Shortcuts::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return Shortcuts::instance(); // C++ and QML instance
}


bool Shortcuts::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() != QEvent::KeyPress)
        return QObject::eventFilter(obj, e);

    qDebug() << e->type();

    return QObject::eventFilter(obj, e);
}


void Shortcuts::init()
{
    Shortcut s;
    s.setKey(Qt::CTRL + Qt::Key_Q);
    //connect(s, s.activated(), this, this->ready());

    //add(QKeySequence(Qt::CTRL + Qt::Key_P), Player::instance(), &Player::togglePlayPause);

    // TODO: hotkeys in c++
    //https://stackoverflow.com/questions/12192780/assigning-keyboard-shortcuts-to-qml-components
    // https://asmaloney.com/2016/03/code/using-c11-lambdas-as-qt-slots/
    // https://code.woboq.org/qt5/qtdeclarative/src/quick/util/qquickshortcut.cpp.html



    /*
    QWidget *parent = nullptr;

    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, parent);
    connect(quitShortcut, &QShortcut::activated, parent, &QCoreApplication::quit);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, parent);
    connect(toggleShortcut, &QShortcut::activated, Player::instance(), &Player::togglePlayPause);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, parent);
    connect(forwardShortcut, &QShortcut::activated, Player::instance(), &Player::skipForward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, parent);
    connect(backwardShortcut, &QShortcut::activated, Player::instance(), &Player::skipBackward);

    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, parent);
    connect(increaseShortcut, &QShortcut::activated, Player::instance(), &Player::volumeUp);

    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, parent);
    connect(decreaseShortcut, &QShortcut::activated, Player::instance(), &Player::volumeDown);
    */
}



void Shortcuts::add(QKeySequence xKeySequence, const QObject *context, const char* slot)
{

}

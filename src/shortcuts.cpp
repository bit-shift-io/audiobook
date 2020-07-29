
#include <QDebug>
#include <QKeySequence>
#include <QMetaMethod>
#include <QMetaObject>
#include <QShortcut>
#include <QKeyEvent>
#include <QLineEdit>
#include <QGraphicsScene>
#include "shortcuts.h"


Shortcuts::Shortcuts(QObject *parent)
    : QObject(parent)
{
    qApp->installEventFilter(this);

    add(QKeySequence::Quit, QCoreApplication::instance(), "quit");
    add(QKeySequence(Qt::Key_Space), Player::instance(), "togglePlayPause");
    add(QKeySequence(Qt::Key_Right), Player::instance(), "skipForward");
    add(QKeySequence(Qt::Key_Left), Player::instance(), "skipBackward");
    add(QKeySequence(Qt::Key_Up), Player::instance(), "volumeUp");
    add(QKeySequence(Qt::Key_Down), Player::instance(), "volumeDown");
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
    // https://stackoverflow.com/questions/12192780/assigning-keyboard-shortcuts-to-qml-components
    if(e->type() == QEvent::KeyRelease) {
        // key release
        mAlreadySent = false;
        return QObject::eventFilter(obj, e);
    }

    if (e->type() != QEvent::KeyPress)
        return QObject::eventFilter(obj, e);

    if ((dynamic_cast<QGraphicsScene*>(obj)) || (obj->objectName() == "blockShortcut") || (dynamic_cast<QLineEdit*>(obj)) )
        return QObject::eventFilter(obj, e);

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    // Just mod keys is not enough for a shortcut, block them just by returning.
    if (keyEvent->key() >= Qt::Key_Shift && keyEvent->key() <= Qt::Key_Alt)
        return QObject::eventFilter(obj, e);

    int keyInt = keyEvent->modifiers() + keyEvent->key();

    for (ShortcutData &shortcut : mShortcuts) {
        if (!mAlreadySent && QKeySequence(keyInt) == shortcut.KeySequence) {
            mAlreadySent = true;
            // execute!
            QMetaObject::invokeMethod(shortcut.Context, shortcut.Slot, Qt::DirectConnection);
            //QMetaObject::invokeMethod(shortcut.Context, shortcut.Slot, Qt::DirectConnection, Q_ARG(QString, "1234"));
            break;
        }
    }

    return QObject::eventFilter(obj, e);
}


void Shortcuts::add(QKeySequence xKeySequence, QObject *xContext, const char* xSlot)
{
    // need to remove the first char from slot
    ShortcutData s;
    s.KeySequence = xKeySequence;
    s.Context = xContext;
    s.Slot = xSlot;
    mShortcuts.append(s);
}


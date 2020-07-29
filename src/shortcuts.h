#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <QObject>
#include <QCoreApplication>
#include <QKeySequence>
#include "player.h"


struct ShortcutData
{
  QKeySequence KeySequence;
  QObject *Context;
  const char *Slot;
};

Q_DECLARE_METATYPE(ShortcutData);


class Shortcuts : public QObject
{
    Q_OBJECT

public:


    Shortcuts(const Shortcuts&) = delete; // disable copy for singleton
    static Shortcuts *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    bool eventFilter(QObject *obj, QEvent *e);

    // https://www.qtcentre.org/threads/8392-How-to-declare-SLOT-as-a-parameter-to-member-function
    void add(QKeySequence xKeySequence, QObject *xContext, const char *Slot); // const QMetaMethod &method
    void remove();


public slots:
    //void ready();

signals:
    void activated();

private:
    bool mAlreadySent = false;
    QVector<ShortcutData> mShortcuts;
    explicit Shortcuts(QObject *parent = nullptr);

};

#endif // SHORTCUTS_H

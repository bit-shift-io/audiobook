#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <QObject>
#include <QCoreApplication>
#include "player.h"

class Shortcuts : public QObject
{
    Q_OBJECT

public:
    Shortcuts(const Shortcuts&) = delete; // disable copy for singleton
    static Shortcuts *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    bool eventFilter(QObject *obj, QEvent *e);

    void init();

    void add(QKeySequence xKeySequence, const QObject *context, const char* slot);


public slots:
    void ready();

signals:
    void activated();

private:
    explicit Shortcuts(QObject *parent = nullptr);

};

#endif // SHORTCUTS_H

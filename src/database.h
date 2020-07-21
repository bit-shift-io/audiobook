#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database() override;

    // init database
    Q_INVOKABLE void init(const QString &dbName, const QString &dbFileName = {});
    void initDatabase();
    void initRequest();
    void reloadExistingDatabase();

signals:

};

#endif // DATABASE_H

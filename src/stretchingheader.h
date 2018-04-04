#ifndef STRETCHINGHEADER_H
#define STRETCHINGHEADER_H

#include <QHeaderView>

class StretchFactors : public QList < int >
{
public:
    StretchFactors() :
        QList()
    {}
    StretchFactors(const StretchFactors &other) :
        QList(other)
    {}
    StretchFactors(const QList < int > &other) :
        QList(other)
    {}

    int factor(int section)
    {
        if (section < count())
            return at(section);
        return 1;
    }
};

class StretchingHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit StretchingHeader(Qt::Orientation orientation, QWidget *parent = 0);

    void setStretchFactors(const StretchFactors &stretchFactors);

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

    void stretch();

protected:
    StretchFactors mStretchFactors;
};

#endif // STRETCHINGHEADER_H

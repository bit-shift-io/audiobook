#include "stretchingheader.h"

StretchingHeader::StretchingHeader(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent)
{
}

void StretchingHeader::setStretchFactors(const StretchFactors &stretchFactors)
{
    mStretchFactors = stretchFactors;
}

void StretchingHeader::resizeEvent(QResizeEvent *event)
{
    QHeaderView::resizeEvent(event);
    if (!mStretchFactors.isEmpty())
        stretch();
}

void StretchingHeader::showEvent(QShowEvent *event)
{
    QHeaderView::showEvent(event);
    if (!mStretchFactors.isEmpty())
        stretch();
}

void StretchingHeader::stretch()
{
    int totalStretch = 0;
    for (int i = 0; i < count(); ++i)
        totalStretch += mStretchFactors.factor(i);
    int oneWidth = width() / totalStretch;
    for (int i = 0; i < count(); ++i)
        resizeSection(i, oneWidth * mStretchFactors.factor(i));
}

#ifndef IFIGURE_H
#define IFIGURE_H

#include <QObject>

class IFigure : public QObject
{
    Q_OBJECT
public:
    explicit IFigure(QObject *parent = 0);

signals:

public slots:
};

#endif // IFIGURE_H

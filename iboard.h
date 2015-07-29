#ifndef IBOARD_H
#define IBOARD_H

#include <QObject>

class IBoard : public QObject
{
    Q_OBJECT
public:
    explicit IBoard(QObject *parent = 0);

signals:

public slots:
};

#endif // IBOARD_H

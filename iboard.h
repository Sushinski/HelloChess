#ifndef IBOARD_H
#define IBOARD_H

#include <QObject>
#include <QSharedPointer>
#include "ifigure.h"

class IFigure;
class IBoard : public QObject
{
    Q_OBJECT
public:
    explicit IBoard(QObject *parent = 0);
    virtual void createBoard()= 0;
    virtual void writeLog() = 0;
    virtual void getLogRecord() const = 0;
    virtual ~IBoard();
signals:
    virtual void figureChanged(int row, int column) = 0;
public slots:
    virtual bool cellClick(int row, int column) = 0;
private:
    QSharedPointer<IFigure*[][]> m_board;
};

#endif // IBOARD_H

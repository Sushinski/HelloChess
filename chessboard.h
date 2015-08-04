#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "iboard.h"

class IFigure;
class ChessBoard : public IBoard
{
public:
    explicit ChessBoard(int board_size, QObject *parent = 0);
    virtual void createBoard();
    virtual void writeLog();
    void getLogRecord() const;
    virtual ~ChessBoard();
signals:
    virtual void figureChanged(int row, int column);
public slots:
    virtual bool cellClick(int row, int column);
private:
    int m_board_size;
    QVector< QVector< QSharedPointer<IFigure> > > m_board;
};

#endif // CHESSBOARD_H

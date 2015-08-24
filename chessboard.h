#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "iboard.h"
#include <QVector>

class IFigure;
class ChessBoard : public IBoard
{
private:
    int m_board_size;
    QVector< QVector< QSharedPointer<IFigure> > > m_board;
    QSharedPointer<IFigure> m_selected_piece;

public:
    explicit ChessBoard(int board_size, QObject *parent = 0);
    void createBoard();
    void writeLog();
    void getLogRecord() const;
    ~ChessBoard(){}
    inline int getBoardDim() const { return m_board_size; }
    const IFigure& pieceAt( int x, int y ) const;
    IFigure& pieceAt( int x, int y );
signals:
    void figureMoved(QSize from, QSize to){}
public slots:
    bool cellClick(int row, int column);
};

#endif // CHESSBOARD_H

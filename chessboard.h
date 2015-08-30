#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "ifigure.h"
//#include "iboard.h"
#include <QVector>
#include <QSharedPointer>


class ChessPiece;
class Rook;
class Pawn;
class Bishop;
class Knight;
class Queen;
class King;
typedef QSharedPointer<ChessPiece> PiecePtr;

class ChessBoard : public QObject
{
    Q_OBJECT
private:
    int m_board_size;
    QVector< QVector< PiecePtr > > m_board;
    PiecePtr m_selected_piece;
    bool b_black_bottom;
public:
    explicit ChessBoard(int board_size, QObject *parent = 0);
    void createBoard();
    void writeLog();
    void getLogRecord() const;
    ~ChessBoard(){}
    inline int getBoardDim() const { return m_board_size; }
    const PiecePtr& pieceAt( int x, int y ) const;
    PiecePtr& pieceAt( int x, int y );
signals:
    void figureMoved(QSize from, QSize to);
public slots:
    bool cellClick(int row, int column);
};

#endif // CHESSBOARD_H

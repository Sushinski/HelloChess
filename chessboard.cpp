#include "chessboard.h"


ChessBoard::ChessBoard(int board_size, QObject *parent) : IBoard(parent), m_board_size(board_size)
{
    m_board = QSharedPointer<IFigure>(new IFigure*[board_size][board_size]{NULL});

}

void ChessBoard::createBoard()
{
    // set initial chess pieces placement
    // let black will be from top side an white - from bottom
    for( int i = 0; i < m_board_size; ++i )
    {
        m_board[0][i] =
        m_board[1][i]=
        m_board[m_board_size-2][i]=
        m_board[m_board_size-1][i]=
    }

}

void ChessBoard::writeLog()
{

}

void ChessBoard::getLogRecord() const
{

}

void ChessBoard::figureChanged(int row, int column)
{

}

bool ChessBoard::cellClick(int row, int column)
{
    QSize turn_coords = QSize(column, row);
    QList<QSize> possible_turns = m_board[row][column]->turn(turn_coords);
}

#include "chessboard.h"
#include"ifigurecreator.h"

ChessBoard::ChessBoard(int board_size, QObject *parent) :
IBoard(parent),
m_board_size(board_size),
m_board(board_size)
{
}

void ChessBoard::createBoard()
{
    // set initial chess pieces placement
   IFigureCreator line_f_l[m_board_size] = { ChessCreator<Rook>(), ChessCreator<Knight>(), ChessCreator<Bishop>(),
                                                ChessCreator<Queen>(), ChessCreator<King>(),
                                                ChessCreator<Bishop>(), ChessCreator<Knight>(), ChessCreator<Rook>() };
   ChessCreator<Pawn> pawn_crtr();
    // let black will be from top side an white - from bottom
    for( int j = 0; j < m_board_size; ++j )
    {
        m_board[0].append(QSharedPointer<IFigure>(line_f_l[i].createFigure(ChessParam(QSize(i, 0), true))));
        m_board[1].append(QSharedPointer<IFigure>(pawn_crtr.createFigure(ChessParam(QSize(i, 1), true))));
        m_board[m_board_size-2].append(QSharedPointer<IFigure>(pawn_crtr.createFigure(ChessParam(QSize(i, m_board_size-2), false))));
        m_board[m_board_size-1].append(QSharedPointer<IFigure>(
                                           line_f_l[m_board_size-1-i].createFigure(ChessParam(QSize(i, m_board_size-1), false))));
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
    if( row >= 0 && row < m_board_size && column >=0 && column < m_board_size )
    {
        QSize turn_coords = QSize(column, row);
        QList<QSize> possible_turns = m_board[row][column]->turn(turn_coords);
}

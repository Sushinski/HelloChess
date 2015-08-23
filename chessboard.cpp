#include "chessboard.h"
#include "ifigurecreator.h"
#include <QSharedPointer>

ChessBoard::ChessBoard(int board_size, QObject *parent) :
IBoard(parent),
m_board_size(board_size),
m_board(board_size)
{
    createBoard();
}

void ChessBoard::createBoard()
{
   typedef QSharedPointer< IFigureCreator<ChessParam> > PieceCreatorPtr;
    // set initial chess pieces placement
   QVector<PieceCreatorPtr> line_f_l;
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Rook>() ));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Knight>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Bishop>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Queen>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<King>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Bishop>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Knight>));
   line_f_l.append( PieceCreatorPtr( new ChessCreator<Rook>));
   PieceCreatorPtr pawn_crtr( new ChessCreator<Pawn>() );
   PieceCreatorPtr empty_cell_crtr( new ChessCreator<EmptyCell>() );

    // let black will be from top side an white - from bottom
    for( int i = 0; i < m_board_size; ++i )
    {
        m_board[0].append(line_f_l[i]->createFigure(ChessParam(QSize(i, 0), true)));
        m_board[1].append(pawn_crtr->createFigure(ChessParam(QSize(i, 1), true)));
        for( int j = 2; j < m_board_size-2; ++j )
        {
            m_board[j].append(empty_cell_crtr->createFigure(ChessParam(QSize(i, j), true)));
        }
        m_board[m_board_size-2].append(pawn_crtr->createFigure(ChessParam(QSize(i, m_board_size-2), false)));
        m_board[m_board_size-1].append(line_f_l[m_board_size-1-i]->createFigure(ChessParam(QSize(i, m_board_size-1), false)));
    }

}

IFigure& ChessBoard::pieceAt( int x, int y )
{
    return const_cast<IFigure&>( static_cast<const ChessBoard*>( this )->pieceAt( x, y ) );
}

const IFigure& ChessBoard::pieceAt( int x, int y ) const
{
    return *(m_board[y][x].data());
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
        QSize turn_coords = QSize( column, row );
        // check if piece clicked for the 1st time
        IFigure& _selected = pieceAt( column, row );
        if( _selected.isClickable() )
            m_selected_piece.reset( &_selected );
        // ToDo
        QVector<QSize> res;
        QScopedPointer< const QList<QSize> > trns(m_board[column][row]->getPossibleTurns( column, row ));
        QList<QSize>::const_iterator it;
        for(it = trns->begin(); it != trns->end(); it++)
        {
            QSize cur_coords = turn_coords + *it;
            if( (cur_coords.height() <= m_board_size) &&
                (cur_coords.width() <= m_board_size)  &&
                (cur_coords.height() > 0 ||
                cur_coords.width() > 0 ))
            res.append(cur_coords);
        }
    }
    return true;
}

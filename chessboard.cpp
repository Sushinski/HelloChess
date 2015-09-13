#include "chessboard.h"
#include "ifigurecreator.h"
#include <QSharedPointer>
#include <iostream>

ChessBoard::ChessBoard(int board_size, QObject *parent) :
QObject(parent),
m_board_size(board_size),
m_board(board_size)
{
    createBoard();
    b_black_bottom = true;
}

void ChessBoard::createBoard()
{
   typedef QSharedPointer< ICreator<ChessPiece, ChessParam> > PieceCreatorPtr;
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
   // PieceCreatorPtr empty_cell_crtr( new ChessCreator<EmptyCell>() );

    // let black will be from bottom side an white - on top
   // todo
    for( int i = 0; i < m_board_size; ++i )
    {
        m_board[0].append(line_f_l[i]->createFigure(ChessParam(QSize(i, 0), true)));
        m_board[1].append(pawn_crtr->createFigure(ChessParam(QSize(i, 1), true)));
        for( int j = 2; j < m_board_size-2; ++j )
            m_board[j].append(QSharedPointer<ChessPiece>(0));
        m_board[m_board_size-2].append(pawn_crtr->createFigure(ChessParam(QSize(i, m_board_size-2), false)));
        m_board[m_board_size-1].append(line_f_l[m_board_size-1-i]->createFigure(ChessParam(QSize(i, m_board_size-1), false)));
    }

}

PiecePtr& ChessBoard::pieceAt( int x, int y )
{
    return const_cast<PiecePtr&>( static_cast<const ChessBoard*>( this )->pieceAt( x, y ) );
}

const PiecePtr& ChessBoard::pieceAt( int x, int y ) const
{
    return m_board[y][x];
}


void ChessBoard::writeLog()
{

}

void ChessBoard::getLogRecord() const
{

}

bool ChessBoard::cellClick(int row, int column)
{
    if( row >= 0 && row < m_board_size && column >=0 && column < m_board_size )
    {
        QSize turn_coords = QSize( column, row );
        // check if piece clicked for the 1st time
        PiecePtr& _selected = pieceAt( column, row );
        if( _selected )
        {
            m_selected_piece.swap(_selected);
            return true;
        }
        else if( !m_selected_piece )
            return false;
        // get possible turns
        QScopedPointer< const QList<QSize> > trns(m_selected_piece->getPossibleTurns( column, row ));
        // current coords
        QSize cur_coords = m_selected_piece->getCoords();
        QList<QSize>::const_iterator it;
        for(it = trns->begin(); it != trns->end(); it++)
        {
            QSize coords_sum = b_black_bottom ^ m_selected_piece->m_bWhite ? cur_coords - *it  : cur_coords + *it;
            if( coords_sum == turn_coords )
            {
                emit figureMoved(cur_coords, QSize(column, row));
                PiecePtr &turned = pieceAt(column, row);
                m_selected_piece->setCoords(turn_coords);
                turned.swap(m_selected_piece);
                return true;
            }
        }      
    }
    return false;
}

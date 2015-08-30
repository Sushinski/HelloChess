#ifndef IFIGURE_H
#define IFIGURE_H

#include "ifigurecreator.h"
#include <QList>
#include <QSize>

class IFigure
{
public:
    IFigure( QSize coords) : m_coords(coords){}
    virtual ~IFigure(){}
    virtual const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const = 0;
    const QSize& getCoords() const { return static_cast<const QSize&>(m_coords); }
    virtual QString getPixmapName() const = 0;
    void setCoords( const QSize& coords ){ m_coords = coords; }
private:
    QSize m_coords;
};


class ChessPiece : public IFigure
{
public:
    ChessPiece(const ChessParam& param ):
    IFigure(param.m_coords),
    m_bWhite( param.m_b_white ){}
    ~ChessPiece(){}
    virtual const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const = 0;
    virtual QString getPixmapName() const = 0;
    bool m_bWhite;
};

class Pawn : public ChessPiece
{
public:
    Pawn( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const { return  QString(m_bWhite ? "://Resourses/white_pawn.png" : "://Resourses/black_pawn.png");  }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        *res << QSize(0, 1) << QSize(0,2);
        return res;
    }
};

class Rook : public ChessPiece
{
public:
    Rook( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const { return QString( m_bWhite ? "://Resourses/white_rook.png" : "://Resourses/black_rook.png"); }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        for(int i = 0; i <= board_x; i++)
            *res << QSize(i, 0) << QSize(-i, 0);
        for(int i = 0; i <= board_y; i++)
            *res << QSize(0, i) << QSize(0, -i);
        return res;
    }
};

class Knight : public ChessPiece
{
public:
    Knight( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const { return QString(m_bWhite ? "://Resourses/white_horse.png" : "://Resourses/black_horse.png"); }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        *res << QSize(1, 2) << QSize(-1, 2) << QSize(1, -2) << QSize(-1, -2);
        return res;
    }
};

class Bishop : public ChessPiece
{
public:
    Bishop( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const
    { return QString(m_bWhite ? "://Resourses/white_bishop.png" : "://Resourses/black_bishop.png"); }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        int max = std::max( board_x, board_y );
        for( int i = 0; i <= max; i++ )
        {
            *res << QSize(i, i) << QSize(-i, i) << QSize(i, -i) << QSize(-i, -i);
        }
        return res;
    }
};

class Queen : public ChessPiece
{
public:
    Queen( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const
    { return QString( m_bWhite ? "://Resourses/white_queen.png" : "://Resourses/black_queen.png"); }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        int max = std::max( board_x, board_y );
        for(int i = 0; i <= max; i++ )
        {
            *res << QSize(i, 0) << QSize(-i, 0) << QSize(0, i) << QSize(0, -i)
                << QSize(i, i) << QSize(-i, i) << QSize(i, -i) << QSize(-i, -i);
        }
        return res;
    }
};


class King : public ChessPiece
{
public:
    King( const ChessParam& param ) : ChessPiece(param){}
    QString getPixmapName() const { return QString(m_bWhite ? "://Resourses/white_king.png" : "://Resourses/black_king.png"); }
    const QList<QSize>* getPossibleTurns( int board_x, int board_y ) const
    {
        QList<QSize>* res = new QList<QSize>();
        *res << QSize(-1, 0) << QSize(-1, 1) << QSize(0, 1) << QSize(1, 1) << QSize(1, 0)
             << QSize(-1, -1) << QSize(0, -1) << QSize(1, -1);
        return res;
    }
};
#endif // IFIGURE_H

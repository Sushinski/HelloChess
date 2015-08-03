#ifndef IFIGURE_H
#define IFIGURE_H

#include "ifigurecreator.h"

class IFigure
{
public:
    IFigure();
    virtual ~IFigure();
    virtual QList<QSize> getPossibleTurns() = 0;
    virtual QList<QSize> turn( QSize turn_coords ) = 0;

};

class ChessPiece : public IFigure
{
public:
    ChessPiece(const IParam& param, QSize coords);
    virtual ~ChessPiece();
    virtual QList<QSize> getPossibleAttack() = 0;
    virtual QList<QSize> turn( QSize turn_coords );
    enum{ firstLine = 0, secondLine = 1, seventhLine = 6, eighthLine = 7 };
    enum{ black = 0, white = 1 };
private:
    QSize m_coords;
};

class Pawn : public ChessPiece
{
public:
    Pawn( const ChessParam& param );
    QList<QSize> getPossibleTurns()
    {
        QList<QSize> res = QList<QSize>() << QSize(0, 1);
        if( m_coords.height() == Pawn::secondLine || m_coords.height() == Pawn::seventhLine )
            res.append(QSize(0,2));
        return res;
    }
    QList<QSize> getPossibleAttack(){ return QList<QSize>() << QSize(1, 1) << QSize(-1, 1); }
    QList<QSize> turn( QSize turn_coords );
};

class Rook : public ChessPiece
{
public:
    Rook( const ChessParam& param );
    QList<QSize> getPossibleTurns()
    {
        QList<QSize> res;
        for(int i = 0; i <= eighthLine; i++)
        {
            res << QSize(i, 0) << QSize(-i, 0) << QSize(0, i) << QSize(0, -i);
        }
        return res;
    }
    QList<QSize> getPossibleAttack(){ return getPossibleTurns(); }
    QList<QSize> turn( QSize turn_coords );
};

class Knight : public ChessPiece
{
public:
    Knight( const ChessParam& param );
    QList<QSize> getPossibleTurns(){ return QList<QSize>() << QSize(1, 2) << QSize(-1, 2) << QSize(1, -2) << QSize(-1, -2); }
    QList<QSize> getPossibleAttack(){ return getPossibleTurns(); }
    virtual QList<QSize> turn( QSize turn_coords );
};

class Bishop : public ChessPiece
{
public:
    Bishop( const ChessParam& param );
    virtual QList<QSize> getPossibleTurns()
    {
        QList<QSize> res;
        for(int i = 0; i <= eighthLine; i++ )
        {
            res << QSize(i, i) << QSize(-i, i) << QSize(i, -i) << QSize(-i, -i);
        }
        return res;
    }
    QList<QSize> getPossibleAttack(){ return getPossibleTurns(); }
    virtual QList<QSize> turn( QSize turn_coords );
};

class Queen : public ChessPiece
{
public:
    Queen( const ChessParam& param );
    QList<QSize> getPossibleTurns()
    {
        QList<QSize> res;
        for(int i = 0; i <= eighthLine; i++ )
        {
            res << QSize(i, 0) << QSize(-i, 0) << QSize(0, i) << QSize(0, -i)
                << QSize(i, i) << QSize(-i, i) << QSize(i, -i) << QSize(-i, -i);
        }
    }
    QList<QSize> getPossibleAttack(){ return getPossibleTurns(); }
    virtual QList<QSize> turn( QSize turn_coords );
};


class King : public ChessPiece
{
public:
    King( const ChessParam& param );
    QList<QSize> getPossibleTurns(){ QList<QSize>() << QSize(-1, 0) << QSize(-1, 1) << QSize(0, 1) << QSize(1, 1) << QSize(1, 0)
                                                    << QSize(-1, -1) << QSize(0, -1) << QSize(1, -1); }
    QList<QSize> getPossibleAttack(){ return getPossibleTurns(); }
    virtual QList<QSize> turn( QSize turn_coords );
};
#endif // IFIGURE_H

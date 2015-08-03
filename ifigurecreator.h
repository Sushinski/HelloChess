#ifndef IFIGURECREATOR
#define IFIGURECREATOR
#include <QSize>

class IParam;
class IFigure;
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;
class IFigureCreator{
public:
    virtual IFigure* createFigure(const IParam& param) = 0;
};

class IParam
{
public:
    IParam( QSize _coords ) : m_coords(_coords){}
    QSize m_coords;
};

class ChessParam : public IParam
{
public:
    ChessParam(QSzie _coords, bool _bwhite ) : IParam(_coords), m_b_white(_bwhite){}
    bool m_b_white;
};

template<typename T>
class ChessCreator : public IFigureCreator
{
public:
    IFigure* createFigure( const IParam& param ){ return new T(param); }
};
/*
class PawnCreator : public IFigureCreator
{
public:
    IFigure* createFigure( const IParam& param ){ return new Pawn(param); }
};

class RookCreator : public IFigureCreator
{
    IFigure* createFigure( const IParam& param ){ return Rook(param); }
};

class KnightCreator : public IFigureCreator
{
    IFigure* createFigure( const IParam& param ){ return Knight(param); }
};

class BishopCreator : public IFigureCreator
{
    IFigure* createFigure( const IParam& param ){ return Bishop(param); }
};

class QueenCreator : public IFigureCreator
{
    IFigure* createFigure( const IParam& param ){ return Queen(param); }
};

class KingCreator : public IFigureCreator
{
    IFigure* createFigure( const IParam& param ){ return King(param); }
};
*/
#endif // IFIGURECREATOR

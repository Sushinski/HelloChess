#ifndef IFIGURECREATOR
#define IFIGURECREATOR
#include <QSize>
#include <QSharedPointer>

class IParam;
class IFigure;
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

class IParam
{
public:
    IParam( QSize _coords ) : m_coords(_coords){}
    QSize m_coords;
};

class ChessParam : public IParam
{
public:
    ChessParam(QSize _coords, bool _bwhite ) : IParam(_coords), m_b_white(_bwhite){}
    bool m_b_white;
};

template<typename P>
class IFigureCreator{
public:
    virtual QSharedPointer<IFigure> createFigure(const P& param) = 0;
    virtual ~IFigureCreator(){}
};


template<typename T>
class ChessCreator : public IFigureCreator<ChessParam>
{
public:
    QSharedPointer<IFigure> createFigure( const ChessParam& param ){ return QSharedPointer<IFigure>(new T(param)); }
};

#endif // IFIGURECREATOR

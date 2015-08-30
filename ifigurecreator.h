#ifndef IFIGURECREATOR
#define IFIGURECREATOR
#include <QSize>
#include <QSharedPointer>

class IParam;
class IFigure;
class ChessPiece;

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

template<typename T1, typename T2 >
class ICreator
{
public:
    ICreator(){}
    virtual ~ICreator(){}
    virtual QSharedPointer<T1> createFigure( const T2& param ) = 0;
};

template<typename T>
class ChessCreator : public ICreator<ChessPiece, ChessParam>
{
public:
    QSharedPointer<ChessPiece> createFigure( const ChessParam& param ){ return QSharedPointer<ChessPiece>(new T(param)); }
};

#endif // IFIGURECREATOR

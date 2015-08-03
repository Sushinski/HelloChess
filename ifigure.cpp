#include "ifigure.h"
#include "ifigurecreator.h"

IFigure::IFigure( const IParam& param, QSize coords ) : m_coords(coords)
{

}

QList<QSize> ChessPiece::turn( QSize turn_coords )
{
    QList<QSize> res;
    QList<QSize> trns = getPossibleTurns();
    QList<QSize>::iterator it;
    for(it = trns.begin(); it != trns.end(); it++)
    {
        QSize cur_coords = m_coords + *it;
        if( cur_coords.height() <= eighthLine &&
            cur_coords.width() <= eighthLine  &&
            cur_coords.height() > 0 ||
            cur_coords.width() > 0 )
        res.append(cur_coords);
    }
    return res;
}




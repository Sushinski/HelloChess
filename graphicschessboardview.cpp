#include "graphicschessboardview.h"
#include "chessboard.h"
#include <QMouseEvent>


GraphicsChessBoardView::GraphicsChessBoardView( int board_size, QWidget* parent  ) :
QGraphicsView(parent),
m_board_size(board_size),
m_cell_size(board_size/8)
{
    initView();
}

GraphicsChessBoardView::~GraphicsChessBoardView()
{

}

void GraphicsChessBoardView::initView()
{
    try
    {
        m_logic_board = QSharedPointer<ChessBoard>( new ChessBoard(8, this) );
        m_scene = QSharedPointer<QGraphicsScene>( new QGraphicsScene(this) );
        m_scene->setSceneRect(0, 0, m_board_size, m_board_size );
        this->setScene( m_scene.data() );
        bool isWhite = true;
        for(int y = 0; y < 8; ++y)
        {
            for(int x = 0; x < 8; ++x)
            {
                // creating cell
                m_scene->addRect( x * m_cell_size, y * m_cell_size, m_cell_size, m_cell_size, QPen(Qt::black),
                                 isWhite ? QBrush(Qt::white) : QBrush(Qt::gray) );
                // creating figure
                m_graphic_pieces.append( createGraphicPiece(  m_logic_board->pieceAt(x, y) ) );
                isWhite = !isWhite;
            }
            isWhite = !isWhite;
        }
    }
    catch(...)
    {

    }
}

void GraphicsChessBoardView::mouseReleaseEvent( QMouseEvent * event )
{
    QSize logic_pos = graphic_to_logic( event->pos() );
    m_logic_board->cellClick( logic_pos.height(), logic_pos.width() );
}

PiecePtr GraphicsChessBoardView::createGraphicPiece( const IFigure& piece ) const
{
    PiecePtr ptr(m_scene->addPixmap(QPixmap(piece.getPixmapName())));
    QPoint coords = logic_to_graphic(piece.getCoords());
    ptr.data()->setPos( coords.x(), coords.y() );
    return ptr;
}

void GraphicsChessBoardView::moveGraphicPiece( const QSize& from, const QSize& to )
{
    QGraphicsItem* selected = this->itemAt( logic_to_graphic( from ) );
    selected->setPos( logic_to_graphic( to ) );
}


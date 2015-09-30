#include "graphicschessboardview.h"
#include "chessboard.h"
#include <QMouseEvent>
#include <QTransform>


GraphicsChessBoardView::GraphicsChessBoardView( int board_size, QWidget* parent  ) :
QGraphicsView(parent),
m_board_size(board_size),
m_cell_size(board_size/8),
m_graphic_pieces(8)
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
                                 isWhite ? QBrush(Qt::blue) : QBrush(Qt::gray) );
                isWhite = !isWhite;
            }
            isWhite = !isWhite;
        }
        // creating figure
        for(int y = 0; y < 8; ++y)
        {
            for(int x = 0; x < 8; ++x)
            {
                PiecePtr pc =  m_logic_board->pieceAt(x, y);
                if( pc )
                    m_graphic_pieces[y].append( createGraphicPiece( *(pc.data()) ) );
                else
                    m_graphic_pieces[y].append(GrPiecePtr(0));
            }
        }
        QObject::connect(m_logic_board.data(), SIGNAL(figureMoved(QSize,QSize)),
                         this, SLOT(moveGraphicPiece(QSize,QSize)));
    }
    catch(...)
    {
    }
}

void GraphicsChessBoardView::mouseReleaseEvent( QMouseEvent * event )
{
    QPoint clk_pt = mapToScene(event->pos()).toPoint();
    QSize logic_pos = graphic_to_logic( clk_pt );
    m_logic_board->cellClick( logic_pos.height(), logic_pos.width() );
}

GrPiecePtr GraphicsChessBoardView::createGraphicPiece( const ChessPiece& piece ) const
{
    GrPiecePtr ptr(m_scene->addPixmap(QPixmap(piece.getPixmapName())));
    QPoint coords = logic_to_graphic(piece.getCoords());
    ptr->setPos( coords.x(), coords.y() );
    ptr->setVisible(true);
    return ptr;
}

void GraphicsChessBoardView::moveGraphicPiece( const QSize& from, const QSize& to )
{
    GrPiecePtr &ptr_from = m_graphic_pieces[from.height()][from.width()];
    GrPiecePtr &ptr_to = m_graphic_pieces[to.height()][to.width()];
    QPoint pt_to = logic_to_graphic( to );
    //QPoint pt_from = logic_to_graphic(from);
    ptr_from->setPos( pt_to.x(), pt_to.y());
    //ptr_to->setPos(pt_from.x(), pt_from.y());
    ptr_from.swap(ptr_to);
}


QVariant GraphicChessboardItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

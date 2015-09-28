#ifndef GRAPHICSCHESSBOARDVIEW_H
#define GRAPHICSCHESSBOARDVIEW_H
#include <QObject>
#include <QSharedPointer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class ChessBoard;
class ChessPiece;
class GraphicChessboardItem : public QGraphicsPixmapItem
{
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};
typedef QSharedPointer<QGraphicsPixmapItem> GrPiecePtr;
class GraphicsChessBoardView : public QGraphicsView
{
    Q_OBJECT
private:
    GrPiecePtr createGraphicPiece(const ChessPiece& piece ) const;
    int m_board_size;
    int m_cell_size;
    QVector< QVector<GrPiecePtr> >m_graphic_pieces;
    QSharedPointer<ChessBoard> m_logic_board;
    QSharedPointer<QGraphicsScene> m_scene;
    inline QPoint logic_to_graphic(const QSize& logic_coords) const
    {
        int x = logic_coords.width() * m_cell_size;
        int y = logic_coords.height() * m_cell_size;
        return QPoint( x, y );
    }
    inline QSize graphic_to_logic(const QPoint& graphic_coords) const { return QSize( graphic_coords.x() / m_cell_size, graphic_coords.y() / m_cell_size ); }
protected:
    void mouseReleaseEvent(QMouseEvent * event);
public:
    GraphicsChessBoardView( int board_size, QWidget* parent = 0);
    void initView();
    ~GraphicsChessBoardView();

public slots:
    void moveGraphicPiece( const QSize& from, const QSize& to );
};

#endif // GRAPHICSCHESSBOARDVIEW_H

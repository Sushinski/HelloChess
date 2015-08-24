#ifndef GRAPHICSCHESSBOARDVIEW_H
#define GRAPHICSCHESSBOARDVIEW_H
#include <QSharedPointer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class ChessBoard;
class IFigure;
typedef QSharedPointer<QGraphicsItem> PiecePtr;
class GraphicsChessBoardView : public QGraphicsView
{
private:
    PiecePtr createGraphicPiece(const IFigure& piece ) const;
    int m_board_size;
    int m_cell_size;

    QVector<PiecePtr>m_graphic_pieces;
    QSharedPointer<ChessBoard> m_logic_board;
    QSharedPointer<QGraphicsScene> m_scene;
    inline QPoint logic_to_graphic(const QSize& logic_coords) const { return QPoint( logic_coords.width() * m_cell_size, logic_coords.height() * m_cell_size ); }
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

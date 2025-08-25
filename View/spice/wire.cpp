#include "wire.h"

#include <qgraphicssceneevent.h>
#include <QPainter>
#include <QObject>

#include "elements.h"

Wire::Wire(Node* startNode, Node* endNode, QGraphicsItem* parent)
    : QGraphicsObject(parent),pathItem(new QGraphicsPathItem(this)), m_startNode(startNode), m_endNode(endNode)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);


    setZValue(-1);
    // Connect to node movement signals
    connect(startNode, &Node::scenePositionChanged, this, &Wire::updatePath);
    connect(endNode, &Node::scenePositionChanged, this, &Wire::updatePath);
    updatePath();

}

Node* Wire::startNode() const {
    return m_startNode;
}

Node* Wire::endNode() const {
    return m_endNode;

}

void Wire::updatePath() {
    QPainterPath path;
    QPointF start = m_startNode->scenePos();
    QPointF end = m_endNode->scenePos();

    // Snap to grid (25 units)
    start = QPointF(qRound(start.x() / GRID_SIZE) * GRID_SIZE,
                   qRound(start.y() / GRID_SIZE) * GRID_SIZE);
    end = QPointF(qRound(end.x() / GRID_SIZE) * GRID_SIZE,
                 qRound(end.y() / GRID_SIZE) * GRID_SIZE);

    path.moveTo(start);

    // Manhattan routing - horizontal then vertical
    if (qAbs(start.x() - end.x()) > qAbs(start.y() - end.y())) {
        path.lineTo(end.x(), start.y());
        path.lineTo(end);
    }
    // Vertical then horizontal
    else {
        path.lineTo(start.x(), end.y());
        path.lineTo(end);
    }

    pathItem->setPath(path);
    prepareGeometryChange();
    QPen pen(isSelected() ? Qt::darkCyan : Qt::black);
    if (isSelected()) {
        pen.setStyle(Qt::DashLine);
    }
    pathItem->setPen(pen);
    update();
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        QPen pen(isSelected() ? Qt::darkCyan : Qt::black);
        if (isSelected()) {
            pen.setStyle(Qt::DashLine);
        }
        pathItem->setPen(pen);
        event->accept();
    }
    QGraphicsObject::mousePressEvent(event);
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(isSelected() ? Qt::blue : Qt::black);
    if (isSelected()) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);

    pathItem->paint(painter,option,widget);
}

QRectF Wire::boundingRect() const {
    return pathItem->boundingRect();
}


QVariant Wire::itemChange(GraphicsItemChange change, const QVariant &value) {

    return QGraphicsObject::itemChange(change, value);

}
void Wire::updateConnection() {
    // Reconnect to nodes if needed
    disconnect(m_startNode, nullptr, this, nullptr);
    disconnect(m_endNode,nullptr, this, nullptr);

    connect(m_startNode, &Node::scenePositionChanged, this, &Wire::updatePath);
    connect(m_endNode, &Node::scenePositionChanged, this, &Wire::updatePath);
    QPen pen(isSelected() ? Qt::darkCyan : Qt::black);
    if (isSelected()) {
        pen.setStyle(Qt::DashLine);
    }
    pathItem->setPen(pen);
    updatePath();
    emit connectionChanged();
}
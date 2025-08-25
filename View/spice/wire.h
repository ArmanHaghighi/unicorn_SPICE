#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsPathItem>
#include <QGraphicsObject>
#include <cereal/access.hpp>

#include "node.h"
using namespace Spice;
class Wire :  public QGraphicsObject{
    Q_OBJECT
public:
    Wire(Node* startNode, Node* endNode, QGraphicsItem* parent = nullptr);

    // Connection management
    Node* startNode() const;
    Node* endNode() const;

    // Update visual representation
    void updatePath();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateConnection();
    template <class Archive>
   void serialize(Archive& ar) {
        ar(startNodeId, endNodeId);
    }

    void setNodeIds(int startId, int endId) { startNodeId = startId; endNodeId = endId; }
    std::pair<int, int> getNodeIds() const { return {startNodeId, endNodeId}; }

    Wire()=default;
    signals:
        void connectionChanged();
// friend class cereal::access;
private:
    QGraphicsPathItem* pathItem;
   Node* m_startNode;
   Node* m_endNode;
    int startNodeId = -1;
    int endNodeId = -1;
};

#endif // WIRE_H
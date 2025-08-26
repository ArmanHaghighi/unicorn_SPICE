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
    Wire(Spice::Node* startNode, Spice::Node* endNode, QGraphicsItem* parent = nullptr);

    // Connection management
    Spice::Node* startNode() const;
    Spice::Node* endNode() const;

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
   Spice::Node* m_startNode;
   Spice::Node* m_endNode;
    int startNodeId = -1;
    int endNodeId = -1;
};

#endif // WIRE_H
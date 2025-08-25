#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QSet>
#include <QGraphicsObject>
#include <set>

#include "mainwindow.h"

namespace Spice {
    class Node : public QGraphicsObject,public  std::enable_shared_from_this<Node>{
        Q_OBJECT
    public:
        // Add these methods:
        int getId() const { return id; }
        void setId(int newId) {
            id = newId;
            if (id >= nextId) nextId = id + 1;
        }
        static int getNextId() { return nextId; }
        static void setNextId(int value) { nextId = value; }
        enum NodeType { Default, Junction };
        explicit Node(Element* parent=nullptr,NodeType type=Default);
        QRectF boundingRect() const override;
        // Identification
        void setName(const QString& name);
        QString name() const;

        // Connection management
        void connectElement(Element* element);
        // Electrical properties
        double voltage() const;
        void setVoltage(double voltage);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        QGraphicsEllipseItem* ellipse;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        NodeType type=Default;
        void setScenePosition(const QPointF& pos);
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        std::set<Node*> m_connectedNodes;
        bool hasCustomName() const;
        void setHasCustomName(bool custom);
        void propagateNameToConnectedNodes(const QString& name);
        template <class Archive>
        void serialize(Archive& ar) {
            ar(m_name, m_hasCustomName, m_voltage);
        }
    public slots:
       // void handleParentMoved();
   signals:
       void positionChanged();
        void scenePositionChanged();
        void namePropagationRequested(Node* source, const QString& name);


    private:
        QString m_name;
        double m_voltage = 0.0;
        QSet<Element*> m_connections;
        bool nameSet=false;
        bool m_hasCustomName = false;
        int id;
        static int nextId;
    };
}
#endif // NODE_H
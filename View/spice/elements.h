#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsItem>
#include <bits/stdc++.h>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

using namespace std;
namespace Spice {
    class Node;
    constexpr double GRID_SIZE =12.5;
    class Element : public QGraphicsItem
    {
    public:
        explicit Element(QGraphicsScene* parent=nullptr);
        QRectF boundingRect() const override;

        // Serialization function
        template <class Archive>
        void serialize(Archive& ar);

        QVector<Spice::Node*> nodes{};
        virtual void addNodes();

        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        virtual void setName(QString name);
        virtual void setValue(QString value);
        // Virtual function to get type name
        virtual QString getTypeName() const = 0;
        QPointF firstLead;
        QPointF secondLead;
        QString getName();
        QString getValue();
        signals:
        void elementMoved();

    protected:


        QString name;
        QString value;
    };

    template<class Archive>
    void Element::serialize(Archive &ar) {
        ar(name, value, firstLead, secondLead);
    }

    class Resistor : public Element {
    public:
        Resistor();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override;
    };
    class Capacitor : public Element {
    public:
        Capacitor();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "Capacitor";}
    };
    class Inductor : public Element {
    public:
        Inductor();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "Inductor";}
    };
    class Gnd : public Element {
    public:
        Gnd();
        void addNodes() override;
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QString getTypeName() const override{return "Gnd";}
    };
    class IdealDiode : public Element {
    public:
        IdealDiode();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "IdealDiode";}
    };
    class SiliconDiode : public IdealDiode {
    public:
        SiliconDiode():IdealDiode(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "SiliconDiode";}
    };

    class DCVoltageSource : public Element {
    public:
        DCVoltageSource();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "DCVoltageSource";}
    };

    class ACVoltageSource : public Element {
    public:
        ACVoltageSource():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QString getTypeName() const override{return "ACVoltageSource";}
    private:
        QString phase;
        QString offset;
    };

    class DCCurrentSource : public Element {
    public:
        DCCurrentSource():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "DCCurrentSource";}
    };

    class ACCurrentSource : public Element {
    public:
        ACCurrentSource():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "ACCurrentSource";}
    };
    class DependantSource : virtual public Element {
    public:
        QPointF thirdLead;
        QPointF fourthLead;
        DependantSource();

        QRectF boundingRect() const override;
        void addNodes() override;
        QString getTypeName() const override{return "DependantSource";}
    };
    class VCVS : public DependantSource {
    public:
        VCVS():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "VCVS";}
    };

    class VCCS : public DependantSource {
    public:
        VCCS():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "VCCS";}
    };

    class CCVS : public DependantSource {
    public:
        CCVS():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "CCVS";}
    };

    class CCCS : public DependantSource {
    public:
        CCCS():Element(){}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setName(QString name) override;
        QString getTypeName() const override{return "CCCS";}
    };
}
    // Serialization for QPointF
    namespace cereal {
        template <class Archive>
        void serialize(Archive& ar, QPointF& point) {
            ar(point.rx(), point.ry());
        }

    }
    // Serialization for QString
    namespace cereal {
        template <class Archive>
        void save(Archive& ar, const QString& str) {
            ar(str.toStdString());
        }

        template <class Archive>
        void load(Archive& ar, QString& str) {
            std::string s;
            ar(s);
            str = QString::fromStdString(s);
        }
    }

using namespace Spice;
    // Register polymorphic types for Cereal
    CEREAL_REGISTER_TYPE(Spice::Resistor);
    CEREAL_REGISTER_TYPE(Spice::Capacitor);
    CEREAL_REGISTER_TYPE(Spice::Inductor);
    CEREAL_REGISTER_TYPE(Spice::Gnd);
    CEREAL_REGISTER_TYPE(Spice::IdealDiode);
    CEREAL_REGISTER_TYPE(Spice::SiliconDiode);
    CEREAL_REGISTER_TYPE(Spice::DCVoltageSource);
    CEREAL_REGISTER_TYPE(Spice::ACVoltageSource);
    CEREAL_REGISTER_TYPE(Spice::DCCurrentSource);
    CEREAL_REGISTER_TYPE(Spice::ACCurrentSource);
    CEREAL_REGISTER_TYPE(Spice::VCVS);
    CEREAL_REGISTER_TYPE(Spice::VCCS);
    CEREAL_REGISTER_TYPE(Spice::CCVS);
    CEREAL_REGISTER_TYPE(Spice::CCCS);

    // Register base class
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::Resistor);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::Capacitor);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::Inductor);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::Gnd);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::IdealDiode);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::SiliconDiode);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::DCVoltageSource);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::ACVoltageSource);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::DCCurrentSource);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::ACCurrentSource);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::VCVS);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::VCCS);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::CCVS);
    CEREAL_REGISTER_POLYMORPHIC_RELATION(Spice::Element,Spice::CCCS);

    #endif // ELEMENTS_H

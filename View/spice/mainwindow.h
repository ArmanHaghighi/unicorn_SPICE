#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMouseEvent>
#include <bits/stdc++.h>
#include "elements.h"
#include "addelementdialog.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
class Scope;
class Wire;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QShortcut;

namespace Spice {
    class SchematicView;
    struct ElementData {
        QString type;
        QString name;
        QString value;
        QPointF pos;
        double rotation;
        QPointF firstLead;
        QPointF secondLead;
        std::vector<int> nodeIds;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(type, name, value, pos, rotation, firstLead, secondLead, nodeIds);
        }
    };

    struct NodeData {
        int id;
        QPointF pos;
        QString name;
        bool hasCustomName;
        QString type;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(id, pos, name, hasCustomName, type);
        }
    };

    struct WireData {
        int startNodeId;
        int endNodeId;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(startNodeId, endNodeId);
        }
    };

    struct CircuitData {
        std::vector<ElementData> elements;
        std::vector<NodeData> nodes;
        std::vector<WireData> wires;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(elements, nodes, wires);
        }
    };
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;
        Ui::MainWindow *ui;
        void deleteSelectedItems();

        void tileSubWindowsVertically(QMdiArea* mdiArea) const ;

        void tidyNodes();
    private slots:

        void on_actionNew_triggered();

        void on_actionOpen_triggered();

        void on_actionSave_triggered();

        void on_actionTransient_triggered();

        void on_actionAc_Sweep_triggered();

        void on_actionDc_Sweep_triggered();

        void on_actionPhase_triggered();

        void on_actionEscape_triggered();


        void on_actionResistor_toggled(bool arg1);

        void on_actionInductor_toggled(bool arg1);

        void on_actionDuplicate_toggled(bool arg1);

        void on_actionDelete_toggled(bool arg1);

        void on_actionWire_toggled(bool arg1);

        void on_actionCapacitor_toggled(bool arg1);

        void on_actionAdd_Element_toggled(bool arg1);

        void on_actionGnd_toggled(bool arg1);

        void handleMouseRelease(QMouseEvent* event);

        Node *createJunctionAt(const QPointF &scenePos);

        void createWire(Node *start, Node *end, Node* wireStartNode = nullptr);

        void handleNodeNamePropagation(Node *source, const QString &name);

        void on_actionAdd_Cursor_triggered();

        void on_actionRemove_Cursor_triggered();

        void on_actionSnap_toggled(bool arg1);

        void on_actionCursor_toggled(bool arg1);

        void on_actionVoltageProbe_triggered(bool checked);

        void on_actionCurrentProbe_triggered(bool checked);

        void on_actionPowerProbe_triggered(bool checked);

    signals:
        void nodeNamePropagationRequested(Node* source, const QString& name);
    private:
        bool saveCircuit(const QString& filename);
        bool loadCircuit(const QString& filename);

        void clearCircuit();

        void resizeEvent(QResizeEvent *event);

        void showEvent(QShowEvent *event);

        SchematicView* schematic=nullptr;
        Scope* scope=nullptr;
        QShortcut *escapeShortcut;
        std::vector<Element*> elements;
        Node* wireStartNode = nullptr;
        std::vector<Wire*> wires;
        QVector<Node*> junctionNodes;
        enum class ToolType {
            None,
            Resistor,
            Capacitor,
            Inductor,
            Wire,
            Gnd,
            IdealDiode,
            SiliconDiode,
            DCVoltageSource,
            ACVoltageSource,
            DCCurrentSource,
            ACCurrentSource,
            tSource,
            VCVS,
            VCCS,
            CCVS,
            CCCS
        };
        ToolType currentTool = ToolType::None;
        int nodeCount=0;
        void placeElementOnClick(QMouseEvent *event);
    };

    class SchematicView :public QGraphicsView{
        Q_OBJECT
    public:
        QGraphicsScene* schematicScene;

        explicit SchematicView(MainWindow* mainWindow);
        SchematicView(QWidget* wid);
        ~SchematicView() override{
            delete schematicScene;
        }
        signals:
            void mousePressed(QMouseEvent* event);
        void mouseReleased(QMouseEvent* event);

    protected:
        void resizeEvent(QResizeEvent *event) override;
        void mousePressEvent(QMouseEvent* event) override ;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void wheelEvent(QWheelEvent *event) override;
    };
}
#endif // MAINWINDOW_H


#include "mainwindow.h"
#include <qlistwidget.h>
#include "./ui_mainwindow.h"
#include "elements.h"
#include <QShortcut>
#include <QMessageBox>
#include <QQueue>
#include <ui_addelementdialog.h>
#include <ui_trandialog.h>
#include "node.h"
#include <ui_ACDialog.h>
#include <ui_DCDialog.h>
#include <ui_phaseDialog.h>
#include "acdialog.h"
#include "trandialog.h"
#include "dcdialog.h"
#include "phasedialog.h"
#include "wire.h"
#include <QFileDialog>
#include <QTimer>

#include "Scope.h"
using namespace std;
using namespace Spice;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (QAction *action : ui->menuFile->actions()) {
        action->setIconVisibleInMenu(false);  // Hides icons in menus
    }
    escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escapeShortcut, &QShortcut::activated, this, &MainWindow::on_actionEscape_triggered);
    connect(escapeShortcut, &QShortcut::activated, this, &MainWindow::on_actionEscape_triggered);

    connect(ui->schematicView,  &SchematicView::mousePressed,
                this, &MainWindow::placeElementOnClick);
    connect(this, &MainWindow::nodeNamePropagationRequested,
        this, &MainWindow::handleNodeNamePropagation);
    schematic = new SchematicView(this);
    scope=new Scope(this,ui->customePlot);
    tileSubWindowsVertically(ui->mdiArea);
//______________________________________________________________________Just for testing TODO:Implement probing system and pass output of simulation to scope
    //TODO: ADD and remove traces
    QVector<double> x(1000), y1(1000), y2(1000);
    for (int i = 0; i < 1000; ++i) {
        x[i] = i / 100.0; // Time from 0 to 10 seconds
        y1[i] = 5 * sin(2 * M_PI * 0.5 * x[i]); // 0.5 Hz sine wave
        y2[i] = 3 * cos(2 * M_PI * 1.0 * x[i]) + QRandomGenerator::global()->bounded(1.0); // 1.0 Hz cosine with noise
    }

    // Add signals to scope
    scope->addSignal(x, y1, "Sine Wave", Qt::blue);
    scope->addSignal(x, y2, "Noisy Cosine", Qt::red);
//_______________________________________________________________________________________
    scope->enableCursors(true);
    on_actionCursor_toggled(true);

}

MainWindow::~MainWindow()
{   delete escapeShortcut;
    delete ui;

}

SchematicView::SchematicView(MainWindow *mainWindow) {
    schematicScene=new QGraphicsScene(mainWindow);
    schematicScene->setSceneRect(-10000,-10000,20000,20000);

    auto schView =mainWindow->ui->schematicView;
    schView->setScene(schematicScene);
    schView->setRenderHint(QPainter::Antialiasing);
    schView->setDragMode(RubberBandDrag);
    schView->setViewportUpdateMode(FullViewportUpdate);
    schView->setResizeAnchor(AnchorUnderMouse);


    QPen gridPen(QColor(220, 220, 220),1,Qt::PenStyle::DotLine);
    for(double x = -10000; x <= 10000; x += GRID_SIZE) {
        QGraphicsLineItem *line = schematicScene->addLine(x, -10000, x, 10000, gridPen);
        line->setZValue(-10);
    }
    for(double y = -10000; y <= 10000; y += GRID_SIZE) {
        QGraphicsLineItem *line =schematicScene->addLine(-10000, y, 10000, y, gridPen);
        line->setZValue(-10);

    }
}

SchematicView::SchematicView(QWidget *wid)
{

}



void SchematicView::resizeEvent(QResizeEvent *event) {

    QGraphicsView::resizeEvent(event);

}

void SchematicView::mousePressEvent(QMouseEvent *event) {
    emit mousePressed(event);
    QGraphicsView::mousePressEvent(event);
}

void SchematicView::mouseReleaseEvent(QMouseEvent *event) {
    emit mouseReleased(event);
    QGraphicsView::mouseReleaseEvent(event);
}

void SchematicView::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() .testFlag(Qt::ControlModifier)) {
        const double scaleFactor =1.15;

        if (event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        }
        else
            scale(1/scaleFactor, 1/scaleFactor);
    }
    else
        QGraphicsView::wheelEvent(event);
}


void MainWindow::on_actionResistor_toggled(bool checked)
    {
        std::cout<<"Resistor"<<std::endl;
        if(checked) {
            currentTool=ToolType::Resistor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionResistor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Resistor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }
void MainWindow::on_actionCapacitor_toggled(bool checked)
    {
        std::cout<<"Cap"<<std::endl;
        if(checked) {
            currentTool=ToolType::Capacitor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionCapacitor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Capacitor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }
    void MainWindow::on_actionInductor_toggled(bool checked)
    {
        std::cout<<"Ind"<<std::endl;
        if(checked) {
            currentTool=ToolType::Inductor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionInductor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Inductor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }





    void MainWindow::on_actionNew_triggered()
    {
        QProcess::startDetached(QApplication::applicationFilePath(), QStringList());

    }


    void MainWindow::on_actionOpen_triggered()
    {
        QString filename = QFileDialog::getOpenFileName(this, "Load Circuit", "", "Circuit Files (*.cir)");
        if (!filename.isEmpty()) {
            loadCircuit(filename);
        }
    }


    void MainWindow::on_actionSave_triggered()
    {
        QString filename = QFileDialog::getSaveFileName(this, "Save Circuit", "", "Circuit Files (*.cir)");
        if (!filename.isEmpty()) {
            saveCircuit(filename);
        }
    }


    // void MainWindow::on_actionAdd_Element_triggered()
    // {
    //     std::cout<<"AddE"<<std::endl;
    //     // disableing other actions
    //
    //     }
    // }


    // void MainWindow::on_actionDuplicate_triggered()
    // {
    //     std::cout<<"Dup"<<std::endl;
    //     // disableing other actions
    //     for(QAction *a:ui->toolBar->actions()){
    //         if (a!=ui->actionDuplicate)
    //             a->setChecked(false);
    //     }
    //
    // }
    //
    //
    // void MainWindow::on_actionDelete_triggered()
    // {
    //     std::cout<<"Del"<<std::endl;
    //     // disableing other actions
    //     for(QAction *a:ui->toolBar->actions()){
    //         if (a!=ui->actionDelete)
    //             a->setChecked(false);
    //     }
    //
    // }


    void MainWindow::on_actionEscape_triggered()
    {
        std::cout<<"Esc"<<std::endl;
        // disableing other actions
        for(QAction *a:ui->toolBar->actions()){
                a->setChecked(false);
        }
    currentTool=ToolType::None;
    ui->schematicView->setCursor(Qt::ArrowCursor);
    }


void MainWindow::on_actionTransient_triggered()
{
    TranDialog *d=new TranDialog(this);
    QString iStop, iStart, iStep;
    if(d->exec()==QDialog::Accepted)
    {
        iStop = d->ui->inputStop->text();
        iStart = d->ui->inputStart->text();
        iStep = d->ui->inputStep->text();
    }
    delete d;
}


    void MainWindow::on_actionAc_Sweep_triggered()
    {
        ACDialog *d=new ACDialog(this);
        QString numOfPts, startFreq, stopFreq, typeOfSweep;
        if(d->exec()==ACDialog::Accepted)
        {
            numOfPts = d->ui->inumOfPts->text();
            startFreq = d->ui->istartFreq->text();
            stopFreq = d->ui->istopFreq->text();
            if(d->ui->linear->isChecked())
                typeOfSweep = "linear";
            else if(d->ui->octave->isChecked())
                typeOfSweep = "octave";
            else if(d->ui->decade->isChecked())
                typeOfSweep = "decade";

        }
        delete d;
    }


    void MainWindow::on_actionDc_Sweep_triggered()
    {
        DCDialog *d=new DCDialog(this);
        QString increment, startValue, stopValue, typeOfSweep;
        if(d->exec()==ACDialog::Accepted)
        {
            increment = d->ui->iIncrement->text();
            startValue = d->ui->iStartVal->text();
            stopValue = d->ui->iStopVal->text();
            if(d->ui->linear->isChecked())
                typeOfSweep = "linear";
            else if(d->ui->octave->isChecked())
                typeOfSweep = "octave";
            else if(d->ui->decade->isChecked())
                typeOfSweep = "decade";

        }
        delete d;
    }


    void MainWindow::on_actionPhase_triggered()
    {
        phaseDialog *d=new phaseDialog(this);
        QString freq, startPhase, stopPhase, numOfPts;
        if(d->exec()==ACDialog::Accepted)
        {
            freq = d->ui->iFreq->text();
            startPhase = d->ui->iStartPhase->text();
            stopPhase = d->ui->iEndPhase->text();
            numOfPts = d->ui->iNumOfPts->text();
        }
        delete d;
    }


void MainWindow::tileSubWindowsVertically(QMdiArea* mdiArea) const {
    if (!mdiArea)
        return;

    // Get only visible, non-minimized subwindows
    QList<QMdiSubWindow*> visibleWindows;
    for (QMdiSubWindow *window : mdiArea->subWindowList()) {
        if (!window->isHidden() && !window->isMinimized())
            visibleWindows.append(window);
    }

    if (visibleWindows.isEmpty())
        return;

    // Critical: Force layout update to ensure valid viewport dimensions
    mdiArea->updateGeometry();
    qApp->processEvents(); // Ensure pending layout events are processed

    QWidget *viewport = mdiArea->viewport();
    if (!viewport || viewport->width() <= 0 || viewport->height() <= 0)
        return; // Still invalid - might need to delay further

    const int windowCount = visibleWindows.size();
    const int windowHeight = viewport->height() / windowCount;
    const int windowWidth = viewport->width();

    int y = 0;
    for (QMdiSubWindow *window : visibleWindows) {
        // Reset to normal state first (critical for geometry changes)
        if (window->isMaximized())
            window->showNormal();

        // Set geometry RELATIVE TO VIEWPORT (0,0 is top-left of viewport)
        window->setGeometry(0, y, windowWidth, windowHeight);
        y += windowHeight;
    }
    }


void MainWindow::tidyNodes() {

}


void MainWindow::placeElementOnClick(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || currentTool == ToolType::None)
        return;

    QPointF screenPos = ui->schematicView->mapToScene(event->pos());
    qreal x,y;
         x = qRound(screenPos.x()/25)*25;
         y = qRound(screenPos.y()/25)*25;
    Element* newElement = nullptr;

    switch(currentTool) {
        case ToolType::Resistor:
            newElement = new Resistor();
            break;
        case ToolType::Capacitor:
            newElement = new Capacitor();
            break;
        case ToolType::Inductor:
            newElement = new Inductor();
            break;
        case ToolType::Gnd:
            newElement = new Gnd();
            if (newElement && !newElement->nodes.isEmpty()) {
                newElement->nodes.first()->setName("Gnd");
                newElement->nodes.first()->setHasCustomName(true); // GND name should not change
            }
            break;
        case ToolType::IdealDiode:
            newElement = new IdealDiode();
            break;
        case ToolType::SiliconDiode:
            newElement = new SiliconDiode();
            break;
        case ToolType::DCVoltageSource:
            newElement = new DCVoltageSource();
            break;
        case ToolType::ACVoltageSource:
            newElement = new ACVoltageSource();
            break;
        case ToolType::DCCurrentSource:
            newElement = new DCCurrentSource();
            break;
        case ToolType::ACCurrentSource:
            newElement = new ACCurrentSource();
            break;
        case ToolType::VCVS:
            newElement = new VCVS();
            break;
        case ToolType::VCCS:
            newElement = new VCCS();
            break;
        case ToolType::CCVS:
            newElement = new CCVS();
            break;
        case ToolType::CCCS:
            newElement = new CCCS();
            break;
        default:
            break;
    }

    if (newElement) {
        schematic->schematicScene->addItem(newElement);
        newElement->setPos(x, y);

        newElement->addNodes();
        elements.emplace_back(newElement);
    }
    if (currentTool == ToolType::Wire && event->button() == Qt::LeftButton) {
        QPointF scenePos = ui->schematicView->mapToScene(event->pos());
        QList<QGraphicsItem*> items = schematic->schematicScene->items(scenePos);
        Node* node = nullptr;
        Wire* wire = nullptr;

        // Find the top-most node or wire at the click position
        for (QGraphicsItem* item : items) {
            if (!node) node = dynamic_cast<Node*>(item);
            if (!wire) wire = dynamic_cast<Wire*>(item);
            if (node || wire) break;
        }

        if (node) {
            if (!wireStartNode) {
                wireStartNode = node;
                node->ellipse->setBrush(Qt::red);
            } else if (wireStartNode != node) {
                createWire(wireStartNode, node);
            } else {
                // Clicked same node - cancel
                wireStartNode->ellipse->setPen(QPen(Qt::darkBlue));
                wireStartNode = nullptr;
            }
        }
        else if (wire) {
            // Create junction point at wire intersection
            Node* junction = createJunctionAt(scenePos);

             // Split the existing wire into two wires
            Node* originalStart = wire->startNode();
            Node* originalEnd = wire->endNode();

            // Remove the original wire
            schematic->schematicScene->removeItem(wire);
            wires.erase(std::remove(wires.begin(), wires.end(), wire), wires.end());
            delete wire;
            // Create new wires from original start to junction and junction to original end
            createWire(originalStart, junction,wireStartNode);
            createWire(junction, originalEnd,wireStartNode);

            if (!wireStartNode) {
                wireStartNode = junction;
                junction->ellipse->setBrush(Qt::red);
            } else {
                createWire(wireStartNode, junction);
            }
        }
        else if (wireStartNode) {
            // Reset if clicked on empty space
            wireStartNode->ellipse->setPen(QPen(Qt::darkBlue));
            wireStartNode->ellipse->setBrush(Qt::NoBrush);
            wireStartNode = nullptr;
        }
        return;
    }

}


void MainWindow::on_actionDuplicate_toggled(bool arg1)
{

}


void MainWindow::on_actionDelete_toggled(bool checked)
{
    if (checked) {
        currentTool = ToolType::None; // Not really a tool, but we need to handle selection

        // Disable other actions
        for (QAction *a : ui->toolBar->actions()) {
            if (a != ui->actionDelete) {
                a->setChecked(false);
            }
        }

        ui->schematicView->setCursor(Qt::ForbiddenCursor);

        // Connect selection changed signal
        connect(ui->schematicView, &SchematicView::mouseReleased,
                this, &MainWindow::deleteSelectedItems);
    } else {
        // Disconnect the signal when delete mode is turned off
        disconnect(ui->schematicView, &SchematicView::mouseReleased,
                   this, &MainWindow::deleteSelectedItems);
        ui->schematicView->setCursor(Qt::ArrowCursor);

    }
}

void MainWindow::deleteSelectedItems() {
    if (!ui->actionDelete->isChecked())
        return;

    auto selection =schematic->schematicScene->selectedItems();
    if (selection.empty())
        return;
    bool del=false;
    if (selection.size() >1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Elements",
                                     "Are you sure you want to delete the selected elements?",
                                     QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
            del=true;
    }
    if (selection.size()<=1) del=true;
   if (del) {
        for (QGraphicsItem* item : selection) {
            // Handle wire deletion
            if (Wire* wire = dynamic_cast<Wire*>(item)) {
                schematic->schematicScene->removeItem(wire);
                wires.erase(std::remove(wires.begin(), wires.end(), wire), wires.end());
                delete wire;
            }
            // Handle node/junction deletion
            else if (Node* node = dynamic_cast<Node*>(item)) {
                // Delete connected wires
                for (auto it = wires.begin(); it != wires.end();) {
                    Wire* wire = *it;
                    if (wire->startNode() == node || wire->endNode() == node) {
                        schematic->schematicScene->removeItem(wire);
                        delete wire;
                        it = wires.erase(it);
                    } else {
                        ++it;
                    }
                }

                // Remove from appropriate container
                if (node->type == Node::Junction) {
                    junctionNodes.erase(std::remove(junctionNodes.begin(), junctionNodes.end(), node),
                                      junctionNodes.end());
                } else {
                    // Find and remove from element's node list
                    for (auto& element : elements) {
                        element->nodes.removeOne(node);
                    }
                }

                schematic->schematicScene->removeItem(node);
                delete node;
            }
            // Handle element deletion
            else if (Element* element = dynamic_cast<Element*>(item)) {
                // Delete connected wires
                for (auto it = wires.begin(); it != wires.end();) {
                    Wire* wire = *it;
                    if (element->nodes.contains(wire->startNode()) ||
                        element->nodes.contains(wire->endNode())) {
                        schematic->schematicScene->removeItem(wire);
                        delete wire;
                        it = wires.erase(it);
                    } else {
                        ++it;
                    }
                }

                elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
                schematic->schematicScene->removeItem(element);
                delete element;
            }
        }
    }
    schematic->schematicScene->clearSelection();
}


void MainWindow::on_actionWire_toggled(bool checked)
{
    if (checked) {
        currentTool = ToolType::Wire;
        for(QAction *a:ui->toolBar->actions()) {
            if (a != ui->actionWire) a->setChecked(false);
        }
        ui->schematicView->setCursor(Qt::CrossCursor);
        wireStartNode = nullptr;
    } else if(currentTool == ToolType::Wire) {
        ui->schematicView->setCursor(Qt::ArrowCursor);
        currentTool = ToolType::None;
        wireStartNode = nullptr;
    }
}


    void MainWindow::on_actionAdd_Element_toggled(bool arg1)
    {
        if (!arg1) {
            ui->actionAdd_Element->setChecked(false);
            currentTool = ToolType::None;
            ui->schematicView->setCursor(Qt::ArrowCursor);
            return;
        }

        // Disable other actions
        for(QAction *a : ui->toolBar->actions()) {
            if (a != ui->actionAdd_Element) {
                a->setChecked(false);
                currentTool = ToolType::None;
                ui->schematicView->setCursor(Qt::ArrowCursor);
            }
        }

        AddElementDialog* addElementDialog = new AddElementDialog(this);
        if (addElementDialog->exec() == QDialog::Accepted) {
            QListWidgetItem* selectedItem = addElementDialog->getUi()->listWidget->currentItem();
            if (selectedItem) {
                QString elementName = selectedItem->text();

                if (elementName == "Resistor") {
                    currentTool = ToolType::Resistor;
                }
                else if (elementName == "Capacitor") {
                    currentTool = ToolType::Capacitor;
                }
                else if (elementName == "Inductor") {
                    currentTool = ToolType::Inductor;
                }
                else if (elementName == "Ground") {
                    currentTool = ToolType::Gnd;
                }
                else if (elementName.contains("Ideal_Diode")) {
                    currentTool = ToolType::IdealDiode;
                }
                else if (elementName.contains("Silicon_Diode")) {
                    currentTool = ToolType::SiliconDiode;
                }
                else if (elementName == "DC_Voltage_Source") {
                    currentTool = ToolType::DCVoltageSource;
                }
                else if (elementName == "AC_Voltage_Source") {
                    currentTool = ToolType::ACVoltageSource;
                } else if (elementName == "DC_Current_Source") {
                    currentTool = ToolType::DCCurrentSource;
                }
                else if (elementName == "AC_Current_Source") {
                    currentTool = ToolType::ACCurrentSource;
                }
                else if (elementName == "VCVS") {
                    currentTool = ToolType::VCVS;
                }
                else if (elementName == "VCCS") {
                    currentTool = ToolType::VCCS;
                }
                else if (elementName == "CCVS") {
                    currentTool = ToolType::CCVS;
                }
                else if (elementName == "CCCS") {
                    currentTool = ToolType::CCCS;
                }


                ui->schematicView->setCursor(Qt::CrossCursor);
            }
        } else {
            ui->actionAdd_Element->setChecked(false);
            currentTool = ToolType::None;
        }

        delete addElementDialog;
    }



void MainWindow::on_actionGnd_toggled(bool checked)
{
    std::cout<<"Gnd"<<std::endl;
    if(checked) {
        currentTool=ToolType::Gnd;
        // disableing other actions
        for(QAction *a:ui->toolBar->actions()){
            if (a!=ui->actionGnd)
                a->setChecked(false);
        }
        ui->schematicView->setCursor(Qt::CrossCursor);
    }
    else if(currentTool==ToolType::Gnd) {
        ui->schematicView->setCursor(Qt::ArrowCursor);
        currentTool=ToolType::None;
        // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
        //                   this, &MainWindow::placeElementOnClick);
    }
}

void MainWindow::handleMouseRelease(QMouseEvent *event) {
}


Node* MainWindow::createJunctionAt(const QPointF& scenePos) {
    // Create new junction node
    Node* junction = new Node(nullptr,Node::Junction);
    junction->setPos(scenePos);
    junction->setFlag(QGraphicsItem::ItemIsMovable);
    junction->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    // Add to scene
    schematic->schematicScene->addItem(junction);
    junctionNodes.push_back(junction);

    return junction;
}
//
// void MainWindow::createWire(Node* start, Node* end,   Node* wireStartNode ) {
//     Wire* wire = new Wire(start, end);
//     schematic->schematicScene->addItem(wire);
//     wires.push_back(wire);
//     start->m_connectedNodes.insert(end);
//     end->m_connectedNodes.insert(start);
//
//     // Reset visual feedback
//     start->ellipse->setBrush(Qt::darkBlue);
//     end->ellipse->setBrush(Qt::darkBlue);
//     if (start->type == Node::Junction) {
//         start->ellipse->setBrush(Qt::yellow);
//     }
//
//     this->wireStartNode = wireStartNode;
// }
void MainWindow::createWire(Node* start, Node* end, Node* wireStartNode) {
    Wire* wire = new Wire(start, end);
    schematic->schematicScene->addItem(wire);
    wires.push_back(wire);
    start->m_connectedNodes.insert(end);
    end->m_connectedNodes.insert(start);

    // Handle name propagation
    if (start->hasCustomName() && !end->hasCustomName()) {
        // Start has a custom name, end doesn't - propagate start's name
        end->setName(start->name());
        end->setHasCustomName(false);
        emit nodeNamePropagationRequested(start, start->name());
    } else if (!start->hasCustomName() && end->hasCustomName()) {
        // End has a custom name, start doesn't - propagate end's name
        start->setName(end->name());
        start->setHasCustomName(false);
        emit nodeNamePropagationRequested(end, end->name());
    } else if (!start->hasCustomName() && !end->hasCustomName()) {
        // Neither has a custom name - give them a common name
        QString commonName = start->name().isEmpty() ? end->name() : start->name();
        if (commonName.isEmpty()) {
            // Generate a new name if both are empty
            commonName = "N" + QString::number(nodeCount++);
        }
        start->setName(commonName);
        end->setName(commonName);
        start->setHasCustomName(false);
        end->setHasCustomName(false);
    }
    else {
        // If both have custom names
        end->setName(start->name());
        end->setHasCustomName(false);
        emit nodeNamePropagationRequested(start, start->name());
    }
    // Reset visual feedback
    start->ellipse->setBrush(Qt::darkBlue);
    end->ellipse->setBrush(Qt::darkBlue);
    if (start->type == Node::Junction) {
        start->ellipse->setBrush(Qt::yellow);
    }

    this->wireStartNode = wireStartNode;
}
void MainWindow::handleNodeNamePropagation(Node* source, const QString& name) {
     if (!source || name.isEmpty()) return;

    // Use BFS to propagate name to all connected nodes
    QSet<Node*> visited;
    QQueue<Node*> queue;
    queue.enqueue(source);
    visited.insert(source);

    while (!queue.isEmpty()) {
        Node* current = queue.dequeue();

        // Skip GND nodes
        if (current->name() == "0") continue;

        // Propagate to all connected nodes
        for (Node* connectedNode : current->m_connectedNodes) {
            if (!visited.contains(connectedNode) && !connectedNode->hasCustomName() && connectedNode->name() != "0") {
                connectedNode->setName(name);
                connectedNode->setHasCustomName(false);
                visited.insert(connectedNode);
                queue.enqueue(connectedNode);
            }
        }
    }
}
bool MainWindow::saveCircuit(const QString& filename) {
    try {
        std::ofstream ofs(filename.toStdString(), std::ios::binary);
        cereal::BinaryOutputArchive archive(ofs);

        CircuitData data;

        // Save elements
        for (Element* element : elements) {
            ElementData ed;
            ed.type = element->getTypeName();
            ed.name = element->getName();
            ed.value = element->getValue();
            ed.pos = element->pos();
            ed.rotation = element->rotation();
            ed.firstLead = element->firstLead;
            ed.secondLead = element->secondLead;

            // Save node IDs
            for (Node* node : element->nodes) {
                ed.nodeIds.push_back(node->getId());
            }

            data.elements.push_back(ed);
        }

        // Save nodes (from elements and junctions)
        for (Element* element : elements) {
            for (Node* node : element->nodes) {
                NodeData nd;
                nd.id = node->getId();
                nd.pos = node->pos();
                nd.name = node->name();
                nd.hasCustomName = node->hasCustomName();
                nd.type = (node->type == Node::Junction) ? "Junction" : "Element";
                data.nodes.push_back(nd);
            }
        }

        for (Node* node : junctionNodes) {
            NodeData nd;
            nd.id = node->getId();
            nd.pos = node->pos();
            nd.name = node->name();
            nd.hasCustomName = node->hasCustomName();
            nd.type = "Junction";
            data.nodes.push_back(nd);
        }

        // Save wires
        for (Wire* wire : wires) {
            WireData wd;
            wd.startNodeId = wire->startNode()->getId();
            wd.endNodeId = wire->endNode()->getId();
            data.wires.push_back(wd);
        }

        archive(data);
        return true;
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Save Error", QString("Failed to save circuit: ") + e.what());
        return false;
    }
}
bool MainWindow::loadCircuit(const QString& filename) {
    try {
        clearCircuit();

        std::ifstream ifs(filename.toStdString(), std::ios::binary);
        cereal::BinaryInputArchive archive(ifs);

        CircuitData data;
        archive(data);

        // Map to store node IDs to node pointers
        std::map<int, Node*> nodeMap;

        // Create elements first
        for (const ElementData& ed : data.elements) {
            Element* element = nullptr;

            if (ed.type == "Resistor") {
                element = new Resistor();
            } else if (ed.type == "Capacitor") {
                element = new Capacitor();
            } else if (ed.type == "Inductor") {
                element = new Inductor();
            } else if (ed.type == "Gnd") {
                element = new Gnd();
            } else if (ed.type == "IdealDiode") {
                element = new IdealDiode();
            } else if (ed.type == "SiliconDiode") {
                element = new SiliconDiode();
            } else if (ed.type == "DCVoltageSource") {
                element = new DCVoltageSource();
            } else if (ed.type == "ACVoltageSource") {
                element = new ACVoltageSource();
            } else if (ed.type == "DCCurrentSource") {
                element = new DCCurrentSource();
            } else if (ed.type == "ACCurrentSource") {
                element = new ACCurrentSource();
            } else if (ed.type == "VCVS") {
                element = new VCVS();
            } else if (ed.type == "VCCS") {
                element = new VCCS();
            } else if (ed.type == "CCVS") {
                element = new CCVS();
            } else if (ed.type == "CCCS") {
                element = new CCCS();
            }

            if (element) {
                schematic->schematicScene->addItem(element);
                element->setName(ed.name);
                element->setValue(ed.value);
                element->setPos(ed.pos);
                element->setRotation(ed.rotation);
                element->firstLead = ed.firstLead;
                element->secondLead = ed.secondLead;


                element->addNodes();

                // Update node IDs and add to map
                for (size_t i = 0; i < ed.nodeIds.size() && i < element->nodes.size(); ++i) {
                    element->nodes[i]->setId(ed.nodeIds[i]);
                    nodeMap[ed.nodeIds[i]] = element->nodes[i];
                }

                elements.push_back(element);
            }
        }

        // Create junction nodes
        for (const NodeData& nd : data.nodes) {
            if (nd.type == "Junction") {
                Node* node = new Node(nullptr, Node::Junction);
                node->setId(nd.id);
                node->setPos(nd.pos);
                node->setName(nd.name);
                node->setHasCustomName(nd.hasCustomName);

                schematic->schematicScene->addItem(node);
                junctionNodes.push_back(node);
                nodeMap[nd.id] = node;
            }
        }

        // Create wires
        for (const WireData& wd : data.wires) {
            if (nodeMap.find(wd.startNodeId) != nodeMap.end() &&
                nodeMap.find(wd.endNodeId) != nodeMap.end()) {
                Wire* wire = new Wire(nodeMap[wd.startNodeId], nodeMap[wd.endNodeId]);
                schematic->schematicScene->addItem(wire);
                wires.push_back(wire);
            }
        }

        return true;
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Load Error", QString("Failed to load circuit: ") + e.what());
        return false;
    }
}
void MainWindow::clearCircuit() {
    // Clear wires first (they depend on nodes)
    for (Wire* wire : wires) {
        schematic->schematicScene->removeItem(wire);
        delete wire;
    }
    wires.clear();

    // Clear junction nodes
    for (Node* node : junctionNodes) {
        schematic->schematicScene->removeItem(node);
        delete node;
    }
    junctionNodes.clear();

    // Clear elements (they own their nodes)
    for (Element* element : elements) {
        schematic->schematicScene->removeItem(element);
        delete element;
    }
    elements.clear();

    // Reset node ID counter
    Node::setNextId(0);
}

// Best practice: Call from resizeEvent or after show()
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMdiArea *mdi = ui->mdiArea;
    if (mdi->subWindowList().size() > 1) {
        tileSubWindowsVertically(mdi);
    }
    QMainWindow::resizeEvent(event);
}

// Or after initial show (using single-shot timer)
void MainWindow::showEvent(QShowEvent *event)
{
    QTimer::singleShot(0, this, [this] {
        tileSubWindowsVertically(ui->mdiArea);
    });
    QMainWindow::showEvent(event);
}

void MainWindow::on_actionAdd_Cursor_triggered()
{
    scope->onAddCursorToggled();
}


void MainWindow::on_actionRemove_Cursor_triggered()
{
    scope->onRemoveCursor();
}


void MainWindow::on_actionSnap_toggled(bool arg1)
{
    scope->setSnapToData(arg1);
}



void MainWindow::on_actionCursor_toggled(bool arg1)
{
    scope->enableCursors(arg1);
}

//==============================    //TODO: Add backednd for probing elements and nodes
void MainWindow::on_actionVoltageProbe_triggered(bool checked)
{
    if (checked) {
        for(QAction *a:ui->toolBar->actions()) {
            if (a != ui->actionVoltageProbe) a->setChecked(false);
        }
        ui->schematicView->setCursor(Qt::PointingHandCursor);

    }
}


void MainWindow::on_actionCurrentProbe_triggered(bool checked)
{
    if (checked) {
        for(QAction *a:ui->toolBar->actions()) {
            if (a != ui->actionCurrentProbe) a->setChecked(false);
        }
        ui->schematicView->setCursor(Qt::SizeHorCursor);
    }
}


void MainWindow::on_actionPowerProbe_triggered(bool checked)
{
    if (checked) {
        for(QAction *a:ui->toolBar->actions()) {
            if (a != ui->actionPowerProbe) a->setChecked(false);
        }
        ui->schematicView->setCursor(QCursor(QPixmap(":/icons/assets/probe.png")));
    }


}
//===========================================================================

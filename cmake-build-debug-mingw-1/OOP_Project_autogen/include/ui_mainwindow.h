/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainwindow.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionTransient;
    QAction *actionAc_Sweep;
    QAction *actionDc_Sweep;
    QAction *actionPhase;
    QAction *actionAdd_Element;
    QAction *actionResistor;
    QAction *actionCapacitor;
    QAction *actionInductor;
    QAction *actionDelete;
    QAction *actionWire;
    QAction *actionGnd;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QWidget *Schematic;
    QGridLayout *gridLayout_2;
    SchematicView *schematicView;
    QWidget *Simulation;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSimulation;
    QMenu *menuSchematic;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1022, 694);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/assets/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/assets/open-folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/assets/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionTransient = new QAction(MainWindow);
        actionTransient->setObjectName(QString::fromUtf8("actionTransient"));
        actionAc_Sweep = new QAction(MainWindow);
        actionAc_Sweep->setObjectName(QString::fromUtf8("actionAc_Sweep"));
        actionDc_Sweep = new QAction(MainWindow);
        actionDc_Sweep->setObjectName(QString::fromUtf8("actionDc_Sweep"));
        actionPhase = new QAction(MainWindow);
        actionPhase->setObjectName(QString::fromUtf8("actionPhase"));
        actionAdd_Element = new QAction(MainWindow);
        actionAdd_Element->setObjectName(QString::fromUtf8("actionAdd_Element"));
        actionAdd_Element->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/assets/electrical-component.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_Element->setIcon(icon3);
        actionResistor = new QAction(MainWindow);
        actionResistor->setObjectName(QString::fromUtf8("actionResistor"));
        actionResistor->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/assets/resistor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionResistor->setIcon(icon4);
        actionCapacitor = new QAction(MainWindow);
        actionCapacitor->setObjectName(QString::fromUtf8("actionCapacitor"));
        actionCapacitor->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/assets/capacitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCapacitor->setIcon(icon5);
        actionInductor = new QAction(MainWindow);
        actionInductor->setObjectName(QString::fromUtf8("actionInductor"));
        actionInductor->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/assets/electrical (3).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInductor->setIcon(icon6);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionDelete->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/assets/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon7);
        actionWire = new QAction(MainWindow);
        actionWire->setObjectName(QString::fromUtf8("actionWire"));
        actionWire->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/assets/wire.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWire->setIcon(icon8);
        actionGnd = new QAction(MainWindow);
        actionGnd->setObjectName(QString::fromUtf8("actionGnd"));
        actionGnd->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/assets/computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGnd->setIcon(icon9);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setViewMode(QMdiArea::SubWindowView);
        Schematic = new QWidget();
        Schematic->setObjectName(QString::fromUtf8("Schematic"));
        gridLayout_2 = new QGridLayout(Schematic);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        schematicView = new SchematicView(Schematic);
        schematicView->setObjectName(QString::fromUtf8("schematicView"));
        schematicView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

        gridLayout_2->addWidget(schematicView, 0, 0, 1, 1);

        mdiArea->addSubWindow(Schematic);
        Simulation = new QWidget();
        Simulation->setObjectName(QString::fromUtf8("Simulation"));
        verticalLayout = new QVBoxLayout(Simulation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(Simulation);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        mdiArea->addSubWindow(Simulation);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1022, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSimulation = new QMenu(menubar);
        menuSimulation->setObjectName(QString::fromUtf8("menuSimulation"));
        menuSchematic = new QMenu(menubar);
        menuSchematic->setObjectName(QString::fromUtf8("menuSchematic"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSchematic->menuAction());
        menubar->addAction(menuSimulation->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuSimulation->addAction(actionTransient);
        menuSimulation->addAction(actionAc_Sweep);
        menuSimulation->addAction(actionDc_Sweep);
        menuSimulation->addAction(actionPhase);
        menuSchematic->addAction(actionAdd_Element);
        menuSchematic->addAction(actionResistor);
        menuSchematic->addAction(actionCapacitor);
        menuSchematic->addAction(actionInductor);
        menuSchematic->addAction(actionWire);
        menuSchematic->addAction(actionGnd);
        menuSchematic->addSeparator();
        menuSchematic->addAction(actionDelete);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionTransient);
        toolBar->addAction(actionAc_Sweep);
        toolBar->addAction(actionDc_Sweep);
        toolBar->addAction(actionPhase);
        toolBar->addSeparator();
        toolBar->addAction(actionAdd_Element);
        toolBar->addAction(actionResistor);
        toolBar->addAction(actionCapacitor);
        toolBar->addAction(actionInductor);
        toolBar->addAction(actionGnd);
        toolBar->addAction(actionWire);
        toolBar->addSeparator();
        toolBar->addAction(actionDelete);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTransient->setText(QCoreApplication::translate("MainWindow", "Transient", nullptr));
        actionAc_Sweep->setText(QCoreApplication::translate("MainWindow", "AC Sweep", nullptr));
        actionDc_Sweep->setText(QCoreApplication::translate("MainWindow", "DC Sweep", nullptr));
        actionPhase->setText(QCoreApplication::translate("MainWindow", "Phase", nullptr));
        actionAdd_Element->setText(QCoreApplication::translate("MainWindow", "Add Element", nullptr));
        actionResistor->setText(QCoreApplication::translate("MainWindow", "Resistor", nullptr));
#if QT_CONFIG(shortcut)
        actionResistor->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCapacitor->setText(QCoreApplication::translate("MainWindow", "Capacitor", nullptr));
#if QT_CONFIG(shortcut)
        actionCapacitor->setShortcut(QCoreApplication::translate("MainWindow", "C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionInductor->setText(QCoreApplication::translate("MainWindow", "Inductor", nullptr));
#if QT_CONFIG(shortcut)
        actionInductor->setShortcut(QCoreApplication::translate("MainWindow", "I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionWire->setText(QCoreApplication::translate("MainWindow", "Resistor", nullptr));
#if QT_CONFIG(shortcut)
        actionWire->setShortcut(QCoreApplication::translate("MainWindow", "W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionGnd->setText(QCoreApplication::translate("MainWindow", "GND", nullptr));
#if QT_CONFIG(tooltip)
        actionGnd->setToolTip(QCoreApplication::translate("MainWindow", "Ground", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionGnd->setShortcut(QCoreApplication::translate("MainWindow", "G", nullptr));
#endif // QT_CONFIG(shortcut)
        Schematic->setWindowTitle(QCoreApplication::translate("MainWindow", "Schematic", nullptr));
        Simulation->setWindowTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSimulation->setTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
        menuSchematic->setTitle(QCoreApplication::translate("MainWindow", "Schematic", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

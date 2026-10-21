//
// Created by Latitude 5420 on 2025-08-26.
//

#pragma once
#include <QObject>
#include <QVector>
#include <QString>
#include <QHash>
#include <memory>
#include "Model/model.h"
#include "Model/solver.h"

class BackendFacade : public QObject {
    Q_OBJECT
public:
    explicit BackendFacade(QObject* parent=nullptr)
        : QObject(parent),
          circuit(std::make_unique<Circuit>()),
          solver(std::make_unique<Solver>(circuit.get())) {}

    // element API
    public slots:
        void ensureGround(QString netName = "0");
    void addResistor(QString name, QString n1, QString n2, double r);
    void addCapacitor(QString name, QString n1, QString n2, double c);
    void addInductor(QString name, QString n1, QString n2, double l);
    void addVdc(QString name, QString p, QString n, double v);
    void addIsrc(QString name, QString p, QString n, double i);
    void addVsin(QString name, QString p, QString n, double vOffset, double vAmp, double freq);

    // netlist management
    void clear();
    void renameNode(QString oldName, QString newName);

    // simulation API
    void freeze(); // index nodes/branches
    void runTransient(double tstop, double dt,
                      QStringList probeNodes); // node names to plot

    signals:
        void elementAdded(QString type, QString name);
    void netlistReady();
    void waveReady(QString node, QVector<double> t, QVector<double> v);
    void simFinished();
    void simError(QString message);

private:
    back::Node* getOrCreateNode(const QString& name);

    std::unique_ptr<Circuit> circuit;
    std::unique_ptr<Solver>  solver;

    // scratch buffers reused between steps
    QVector<double> time;
    QHash<QString, QVector<double>> traces;
};

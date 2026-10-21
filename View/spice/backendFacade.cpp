//
// Created by Latitude 5420 on 2025-08-26.
//
// BackendFacade.cpp
#include "BackendFacade.h"
#include <stdexcept>

using namespace back;

back::Node* BackendFacade::getOrCreateNode(const QString& qname) {
    std::string name = qname.toStdString();
    for (back::Node* n : circuit->getNodes()) if (n->getName()==name) return n;
    back::Node* n = new back::Node(name);
    //circuit->addNode(n);
    return n;
}

void BackendFacade::ensureGround(QString netName) {
    std::string g = netName.toStdString();
    for (auto* n : circuit->getNodes())
        if (n->getName()==g) return;
    //auto* gnd = new Ground(g);
    //circuit->addNode(gnd);
}

void BackendFacade::addResistor(QString name, QString n1, QString n2, double r) {
    auto *a = getOrCreateNode(n1), *b = getOrCreateNode(n2);
    circuit->addElement(new Resistor(name.toStdString(), a, b, r));
    emit elementAdded("R", name);
}
void BackendFacade::addCapacitor(QString name, QString n1, QString n2, double c) {
    auto *a=getOrCreateNode(n1), *b=getOrCreateNode(n2);
    circuit->addElement(new Capacitor(name.toStdString(), a, b, c));
    emit elementAdded("C", name);
}
void BackendFacade::addInductor(QString name, QString n1, QString n2, double l) {
    auto *a=getOrCreateNode(n1), *b=getOrCreateNode(n2);
    circuit->addElement(new Inductor(name.toStdString(), a, b, l));
    emit elementAdded("L", name);
}
void BackendFacade::addVdc(QString name, QString p, QString n, double v) {
    auto *a=getOrCreateNode(p), *b=getOrCreateNode(n);
    circuit->addElement(new VoltageSource(name.toStdString(), a, b, v));
    emit elementAdded("V", name);
}
void BackendFacade::addIsrc(QString name, QString p, QString n, double i) {
    auto *a=getOrCreateNode(p), *b=getOrCreateNode(n);
    circuit->addElement(new CurrentSource(name.toStdString(), a, b, i));
    emit elementAdded("I", name);
}
void BackendFacade::addVsin(QString name, QString p, QString n,
                            double vOffset, double vAmp, double freq) {
    auto *a=getOrCreateNode(p), *b=getOrCreateNode(n);
    // Your repo has VoltageSin with offset/amp/freq + stampTransient
    circuit->addElement(new VoltageSin(name.toStdString(), a, b, vOffset, vAmp, freq));
    emit elementAdded("VSIN", name);
}

void BackendFacade::clear() {
    // Depends on your Circuit API; do a simple re-create to keep it short:
    circuit = std::make_unique<Circuit>();
    solver  = std::make_unique<Solver>(circuit.get());
}

void BackendFacade::renameNode(QString oldName, QString newName) {
    for (auto* n : circuit->getNodes())
        if (n->getName()==oldName.toStdString()) { n->renameNode(newName.toStdString()); return; }
}

void BackendFacade::freeze() {
    ensureGround("0");
    try {
        solver->freeze(); // calls across nodes/elements, assigns indices, resizes G/RHS
        emit netlistReady();
    } catch (const std::exception& e) {
        emit simError(QString("freeze() failed: %1").arg(e.what()));
    }
}

void BackendFacade::runTransient(double tstop, double dt, QStringList probeNodes) {
    if (dt <= 0 || tstop <= 0 || dt > tstop) { emit simError("Bad dt/tstop"); return; }
    if (probeNodes.empty()) { emit simError("No nodes to simulate"); return; }
    // prep buffers
    time.clear();
    traces.clear();
    for (const auto& pn : probeNodes) traces.insert(pn, QVector<double>{});

    Solver::Opt opt;
    opt.mode = Solver::Mode::TRAN;
    opt.dt   = dt;

    const int steps = int(std::ceil(tstop/dt));
    time.reserve(steps+1);
    for (auto& v : traces) v.reserve(steps+1);

    // first step hint for elements with history (caps/inds/diodes)
    solver->firstStep = true;
    double t = 0.0;

    for (int k=0; k<=steps; ++k, t = k*dt) {
        opt.t = t;
        const Eigen::VectorXd& x = solver->solveOnce(opt);  // uses stampTransient(...)
        // Persist node voltages for UI:
        time.push_back(t);
        for (const auto& pn : probeNodes) {
            // find node by name, read voltage; your Node has getIdx()/getVoltage()
            double v = 0.0;
            back::Node* node = nullptr;
            for (auto* n : circuit->getNodes())
                if (n->getName()==pn.toStdString()) { node = n; break; }
            if (node) {
                int idx = node->getIdx();
                if (idx >= 0 && idx < x.size()) v = x(idx); // consistent with your Solver::RHS meaning
                else v = node->getVoltage(); // fallback if you store it there
            }
            traces[pn].push_back(v);
        }
        solver->firstStep = false;
    }

    for (const auto& pn : probeNodes)
        emit waveReady(pn, time, traces[pn]);
    emit simFinished();
}

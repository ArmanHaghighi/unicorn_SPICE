//
// Created by Arman on 5/27/2025.
//

#include "model.h"
#include "solver.h"
#include "../Controller/controller.h"

//circuit
void Circuit::initializeCurrentVector() {
    currentVector = VectorXd(nodes.size());
    currentVector.setZero();  // Initialize current vector to zero
}

void Circuit::initializeConductanceMatrix() {
    conductanceMatrix = MatrixXd(nodes.size(), nodes.size());
    conductanceMatrix.setZero();
}

Element* Circuit::checkElementNameExistence(const string& name) const {
    for (auto el:elements) {
        if (el->getName()==name) {
            return el;
        }
    }
    return nullptr;
}

Node* Circuit::checkNodeNameExistence(const string& name) const {
    for (auto n:nodes) {
        if (n->getName()==name) {
            return n;
        }
    }
    return nullptr;
}

void Circuit::addElement(Element *element) {
    elements.emplace(element);
    Node* n1 = element->node1;
    Node* n2 = element->node2;


    if (n1 == nullptr || n2 == nullptr) {
        cerr << "Error: One of the nodes is uninitialized!" << endl;
        return;
    }
    if (n1->idx == -1) {
        n1->idx = Controller::next++;
    }
    if (n2->idx == -1) {
        n2->idx = Controller::next++;
    }

    // Add the nodes if not already present
    if (!nodes.contains(n1)) {
        nodes.emplace(n1);
    }
    if (!nodes.contains(n2)) {
        nodes.emplace(n2);
    }

    solver->resizeMatrix();  // update matrix size after node addition

    element->node1->connectElement(element);
    element->node2->connectElement(element);
}


void Circuit::removeElement(Element *element) {
    if (element->node1->removeElement(element))
        removeNode(element->node1);
    if (element->node2->removeElement(element))
        removeNode(element->node2);
    elements.erase(element);
}

void Circuit::removeNode(Node *node) {
    nodes.erase(node);
    delete node;
}

MatrixXd Circuit::getMatrix() {
    return conductanceMatrix;
}

set<Node*> Circuit::getNodes() {
    return nodes;
}

set<Element*> Circuit::getElements() {
    return elements;
}

//nodes
string Node::getName() {
    return name;
}

void Node::connectElement(Element *element) {
    elements.emplace(element,nullopt);
}

bool Node::removeElement(Element *element) {
    elements.erase(element);
    return elements.empty();
}

double Node::KCL_CurrentCalc(Element* except) {
    double sum = 0;
    for (auto &[e, _] : elements)
        if (e != except) sum += (this == e->node1 ? +1 : -1) * e->getCurrent();
    return sum;
}

double Node::getVoltage() {
    return voltage;
}

void Node::renameNode(string name) {
    this->name = name;
}

map<Element *, double> Node::returnConnectedElements() {
    map<Element *, double> connectedElements;
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        pair<Element*,double>p;
        p.first = it->first;
        if (it->second == nullopt)
            p.second = NAN;
        else
            p.second=it->second.value();
        connectedElements.insert(p);
    }
    return connectedElements;
}

void Node::makeGround() {
    const string n = getName();
    int i =idx;
    this->~Node();
    new(this) Ground(n,i);
}

//elements in general
string Element::getName() {
    return name;
}

//ground
void Ground::makeNode() {
    const string n = getName().erase(getName().size()-5);
    int i =idx;
    this->~Ground();
    new(this) Node(n,i);
}

string Ground::getName() {
    return Node::getName()+"(gnd)";
}

//resistors
void Resistor::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for Resistor: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }

    double g = 1.0 / value;

    G(n1, n1) += g;
    G(n2, n2) += g;
    G(n1, n2) -= g;
    G(n2, n1) -= g;
}


void Resistor::stampDC(MatrixXd& G, VectorXd& I) {
    double g = 1.0 / value;
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    G(n1,n1) += g; G(n2,n2) += g; G(n1,n2) -= g; G(n2,n1) -= g;
}

void Resistor::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    double g = 1.0 / value;
    int n1 = node1->getIdx(), n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for Resistor: " << n1 << ", " << n2 << endl;
        throw std::out_of_range("Node index out of range");
    }

    G(n1, n1) += g;
    G(n2, n2) += g;
    G(n1, n2) -= g;
    G(n2, n1) -= g;
}

//capacitors
void Capacitor::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for Capacitor: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }

    double gc = value / lastDt;

    G(n1, n1) += gc;
    G(n2, n2) += gc;
    G(n1, n2) -= gc;
    G(n2, n1) -= gc;
}

double Capacitor::getCurrent() {
    double dV = node1->getVoltage() - node2->getVoltage() - prevVoltage;
    prevVoltage = node1->getVoltage() - node2->getVoltage();
    return (dV / lastDt) * value; // i(t) = C * dV/dt
}


void Capacitor::stampDC(MatrixXd&, VectorXd&) {} //for dc

/*void Capacitor::stampTransient(MatrixXd& G, VectorXd& I, double dt, double, bool first) {
    double GC = value / dt;
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    G(n1,n1) += GC;
    G(n2,n2) += GC;
    G(n1,n2) -= GC;
    G(n2,n1) -= GC;

    double Ieq = GC * prevVoltage;
    I(n1) -= Ieq;
    I(n2) += Ieq;
}*/

/*void Capacitor::stampTransient(MatrixXd& G, VectorXd& RHS, double dt, double t, bool initial) {
    if (initial) {
        prevVoltage = 0.0;
    }

    double conductance = value / dt;
    double currentSource = conductance * prevVoltage;

    int n1 = node1->getIdx(), n2 = node2->getIdx();

    if (n1 >= 0) {
        G(n1, n1) += conductance;
        RHS(n1) += currentSource;
    }
    if (n2 >= 0) {
        G(n2, n2) += conductance;
        RHS(n2) += currentSource;
    }
    if (n1 >= 0 && n2 >= 0) {
        G(n1, n2) -= conductance;
        G(n2, n1) -= conductance;
        RHS(n1) -= currentSource;
        RHS(n1) -= currentSource;
    }
}*/
// In model.cpp:

void Capacitor::stampTransient(MatrixXd& G, VectorXd& I, double dt, double /*t*/, bool /*first*/) {
    double Gc  = value / dt;
    double Ieq = Gc * prevVoltage;

    int n1 = node1->getIdx();
    int n2 = node2->getIdx();

    //std::cout
    //       << " prevV=" << prevVoltage
    //       << " dt=" << dt
    //       << " -> Gc=" << Gc
    //       << " Ieq=" << Ieq << "\n"; // temp

    G(n1, n1) += Gc;
    G(n2, n2) += Gc;
    G(n1, n2) -= Gc;
    G(n2, n1) -= Gc;

    I(n1) += Ieq;
    I(n2) -= Ieq;
}

void Capacitor::postStepUpdate(double /*dt*/) {
    prevVoltage = node1->getVoltage() - node2->getVoltage();
}

/*void Capacitor::postStepUpdate(double dt) {
    lastDt = dt; //temp
    double v1 = node1->getVoltage();
    double v2 = node2->getVoltage();
    double V = v1 - v2;
    cachedCurrent = value * (V - prevVoltage) / dt; //temp
    prevVoltage = V;

    //cout << "dt=" << dt << ", V=" << node1->getVoltage() - node2->getVoltage() << ", Icap=" << cachedCurrent << endl; //temporary
}*/

// DC voltage source
void VoltageSource::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int k = currentIdx;

    if (n1 < 0 || n2 < 0 || k < 0) {
        cerr << "Invalid node indices for VoltageSource: " << n1 << ", " << n2 << ", " << k << endl;
        throw out_of_range("Node index out of range");
    }

    G(k, n1) = 1;
    G(k, n2) = -1;
    G(n1, k) = 1;
    G(n2, k) = -1;
}

void VoltageSource::stampDC(MatrixXd& G, VectorXd& I) {
    //int n1=node1->getIdx(),n2=node2->getIdx(),k=currentIdx;
    //G(k,n1)=1; G(k,n2)=-1; G(n1,k)=1; G(n2,k)=-1;
    //I(k)=value;
}

void VoltageSource::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    int k = currentIdx;

    if (n1 < 0 || n2 < 0 || k < 0) {
        cerr << "Invalid node indices for VoltageSource: " << n1 << ", " << n2 << ", " << k << endl;
        throw out_of_range("Node index out of range");
    }

    G(k, n1) += 1;
    G(k, n2) += -1;
    G(n1, k) += 1;
    G(n2, k) += -1;
    //RHS(currentIdx) += voltage;
    I(k) = value;
}


// sinusoidal voltage source
void VoltageSin::addToMatrix(MatrixXd &matrix) {}

void VoltageSin::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;
    double v = vOffset + vAmp * sin(2 * M_PI * freq * t);
    G(k,n1) = 1; G(k,n2) = -1;
    G(n1,k) = 1; G(n2,k) = -1;
    I(k) = v;
}

void VoltageSin::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;
    G(k,n1) = 1; G(k,n2) = -1; G(n1,k) = 1; G(n2,k) = -1;
    I(k) = vOffset; // fallback to DC offset
}

// inductors
void Inductor::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int k = currentIdx;

    if (n1 < 0 || n2 < 0 || k < 0) {
        cerr << "Invalid node indices for Inductor: " << n1 << ", " << n2 << ", " << k << endl;
        throw out_of_range("Node index out of range");
    }

    double inductance = value;
    double R = 1.0 / inductance;

    G(k, n1) = 1;
    G(k, n2) = -1;
    G(n1, k) = 1;
    G(n2, k) = -1;
    G(k, k) = -R;
}

double Inductor::getCurrent() {
    return cachedCurrent;
}

void Inductor::stampDC(MatrixXd& G, VectorXd& I){ /* short in DC */ }

void Inductor::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    double R = value / dt;  // inductor's resistance for transient analysis: L * di/dt
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;

    if (n1 < 0 || n2 < 0 || k < 0) {
        cerr << "Invalid node indices for Inductor: " << n1 << ", " << n2 << ", " << k << endl;
        throw out_of_range("Node index out of range");
    }

    G(k, n1) += 1;
    G(k, n2) += -1;
    G(n1, k) += 1;
    G(n2, k) += -1;
    G(k, k) += -R;

    I(k) = -R * prevCurrent;

    prevCurrent = cachedCurrent;
}


void Inductor::postStepUpdate(double dt){ lastDt=dt; prevCurrent=cachedCurrent; }

// dc current source
void CurrentSource::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for CurrentSource: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }
}

void CurrentSource::stampDC(MatrixXd& G, VectorXd& I) {
    //int n1 = node1->getIdx(), n2 = node2->getIdx();
    //I(n1) -= value;
    //I(n2) += value;
}

void CurrentSource::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for CurrentSource: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }

    I(n1) -= value;
    I(n2) += value;
}


// diodes
void Diode::addToMatrix(MatrixXd &G) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for Diode: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }
}

double Diode::getCurrent() {
    return cachedCurrent;
}

void Diode::stampDC(MatrixXd&, VectorXd&) {}

void Diode::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    double voltage = node1->getVoltage() - node2->getVoltage();
    double diodeCurrent = 0;

    int n1 = node1->getIdx(), n2 = node2->getIdx();

    if (n1 < 0 || n2 < 0) {
        cerr << "Invalid node indices for Diode: " << n1 << ", " << n2 << endl;
        throw out_of_range("Node index out of range");
    }

    diodeCurrent = voltage > 0 ? exp(voltage) - 1 : 0;

    I(n1) -= diodeCurrent;
    I(n2) += diodeCurrent;
}


// diode: zener
void Zener::addToMatrix(MatrixXd &matrix) {}

double Zener::getCurrent() {
    return cachedCurrent;
}

void Zener::stampDC(MatrixXd&, VectorXd&) {}

void Zener::stampTransient(MatrixXd&, VectorXd&, double, double, bool) {}

// DEPENDENT SOURCES
// current controlled voltage source
CCVS::CCVS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain)
    : Element(name, n1, n2, gain), controllingElement(ctrlElem), gain(gain) {}

void CCVS::addToMatrix(MatrixXd &matrix) {
    int size = matrix.rows();
    if (currentIdx >= size) {
        matrix.conservativeResize(currentIdx + 1, currentIdx + 1);
        matrix.row(currentIdx).setZero();
        matrix.col(currentIdx).setZero();
    }
}

double CCVS::getCurrent() {
    return node1->KCL_CurrentCalc(this);
}

void CCVS::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int k = currentIdx;
    int ctrlIdx = controllingElement->currentIdx;

    G(k, n1) = 1;
    G(k, n2) = -1;
    G(n1, k) = 1;
    G(n2, k) = -1;
    G(k, ctrlIdx) = -gain;
}

void CCVS::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    int k = currentIdx;
    int ctrlIdx = controllingElement->currentIdx;
    G(k, n1) = 1; G(k, n2) = -1;
    G(n1, k) = 1; G(n2, k) = -1;
    G(k, ctrlIdx) = -gain;
}

// current controlled current source
CCCS::CCCS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain)
    : Element(name, n1, n2, gain), controllingElement(ctrlElem), gain(gain) {}

void CCCS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for CCCS
}

double CCCS::getCurrent() {
    return gain * controllingElement->getCurrent();
}

void CCCS::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int ctrlIdx = controllingElement->currentIdx;

    G(n1, ctrlIdx) += gain;
    G(n2, ctrlIdx) -= gain;
}

void CCCS::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    int ctrlIdx = controllingElement->currentIdx;
    G(n1, ctrlIdx) += gain;
    G(n2, ctrlIdx) -= gain;
}

// voltage controlled current source
VCCS::VCCS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain)
    : Element(name, n1, n2, gain), controlNode1(ctrlN1), controlNode2(ctrlN2), gain(gain) {}

void VCCS::addToMatrix(MatrixXd &matrix) {
    int size = matrix.rows();
    if (currentIdx >= size) {
        matrix.conservativeResize(currentIdx + 1, currentIdx + 1);
        matrix.row(currentIdx).setZero();
        matrix.col(currentIdx).setZero();
    }
}

double VCCS::getCurrent() {
    return gain * (controlNode1->getVoltage() - controlNode2->getVoltage());
}

void VCCS::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int c1 = controlNode1->getIdx();
    int c2 = controlNode2->getIdx();

    G(n1, c1) += gain;
    G(n1, c2) -= gain;
    G(n2, c1) -= gain;
    G(n2, c2) += gain;
}

void VCCS::stampDC(Eigen::MatrixXd &G, Eigen::VectorXd &I) {
}

// voltage controlled voltage source
VCVS::VCVS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain)
    : Element(name, n1, n2, gain), controlNode1(ctrlN1), controlNode2(ctrlN2), gain(gain) {}

void VCVS::addToMatrix(MatrixXd &matrix) {
    int size = matrix.rows();
    if (currentIdx >= size) {
        matrix.conservativeResize(currentIdx + 1, currentIdx + 1);
        matrix.row(currentIdx).setZero();
        matrix.col(currentIdx).setZero();
    }
    double voltageGain = gain;

    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int c1 = controlNode1->getIdx();
    int c2 = controlNode2->getIdx();

    matrix(n1, c1) -= voltageGain;
    matrix(n1, c2) += voltageGain;
    matrix(n2, c1) += voltageGain;
    matrix(n2, c2) -= voltageGain;

    matrix(currentIdx, n1) = 1;
    matrix(currentIdx, n2) = -1;
    matrix(n1, currentIdx) = 1;
    matrix(n2, currentIdx) = -1;
}


double VCVS::getCurrent() {
    return node1->KCL_CurrentCalc(this);
}

void VCVS::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx();
    int n2 = node2->getIdx();
    int c1 = controlNode1->getIdx();
    int c2 = controlNode2->getIdx();
    int k = currentIdx;

    G(k, n1) = 1;
    G(k, n2) = -1;
    G(n1, k) = 1;
    G(n2, k) = -1;
    G(k, c1) -= gain;
    G(k, c2) += gain;
}

void VCVS::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    int c1 = controlNode1->getIdx(), c2 = controlNode2->getIdx();
    int k = currentIdx;
    G(k, n1) = 1; G(k, n2) = -1;
    G(n1, k) = 1; G(n2, k) = -1;
    G(k, c1) -= gain;
    G(k, c2) += gain;
}

void Circuit::analyseTRAN(double dt, double stop, double start) {
    if (!solver)
        solver = new Solver(this);
    solver->freeze();

    results.clear();
    Solver::Opt opt{Solver::Mode::TRAN, dt, start};
    for (double t = start; t < stop; t += dt) {
        opt.t = t;
        const VectorXd& sol = solver->solveOnce(opt);
        results.push_back({t, sol});
    }
    cout << "Transient analysis completed. Results are available." << endl;
}






VectorXd Circuit::analyseDC(){
    if (!solver)
        solver = new Solver(this);
    solver->freeze();
    const auto& x = solver->solveOnce({Solver::Mode::DC});
    return x;
}



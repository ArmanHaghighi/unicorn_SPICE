//
// Created by Arman on 5/27/2025.
//

#include "model.h"
#include "solver.h"

//circuit
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
    if (!nodes.contains(element->node1))
        nodes.emplace(element->node1);
    if (!nodes.contains(element->node2))
        nodes.emplace(element->node2);
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
    this->~Node();
    new(this) Ground(n);
}

//elements in general
string Element::getName() {
    return name;
}

//ground
void Ground::makeNode() {
    const string n = getName().erase(getName().size()-5);
    this->~Ground();
    new(this) Node(n);
}

string Ground::getName() {
    return Node::getName()+"(gnd)";
}

//resistors
void Resistor::addToMatrix(MatrixXd &matrix) {}

void Resistor::stampDC(MatrixXd& G, VectorXd& I) {
    double g = 1.0 / value;
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    G(n1,n1) += g; G(n2,n2) += g; G(n1,n2) -= g; G(n2,n1) -= g;
}

void Resistor::stampTransient(MatrixXd& G, VectorXd& I,double, double, bool) {
    stampDC(G,I);
}

//capacitors
void Capacitor::addToMatrix(MatrixXd &matrix) {}

double Capacitor::getCurrent() {
    return cachedCurrent;
}

void Capacitor::stampDC(MatrixXd&, VectorXd&) {} //for dc

void Capacitor::stampTransient(MatrixXd& G, VectorXd& I, double dt, double, bool first) {
    double GC = value / dt;
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    G(n1,n1) += GC;
    G(n2,n2) += GC;
    G(n1,n2) -= GC;
    G(n2,n1) -= GC;

    double Ieq = GC * prevVoltage;
    I(n1) -= Ieq;
    I(n2) += Ieq;
}

void Capacitor::postStepUpdate(double dt) {
    lastDt = dt;
    double v1 = node1->getVoltage();
    double v2 = node2->getVoltage();
    double V = v1 - v2;
    cachedCurrent = value * (V - prevVoltage) / dt;
    prevVoltage = V;

    cout << "t=" << dt << ", V=" << node1->getVoltage() - node2->getVoltage() << ", Icap=" << cachedCurrent << endl; //temporary
}

// DC voltage source
void VoltageSource::addToMatrix(MatrixXd &matrix) {}

void VoltageSource::stampDC(MatrixXd& G, VectorXd& I) {
    int n1=node1->getIdx(),n2=node2->getIdx(),k=currentIdx;
    G(k,n1)=1; G(k,n2)=-1; G(n1,k)=1; G(n2,k)=-1;
    I(k)=value;
}

void VoltageSource::stampTransient(MatrixXd& G, VectorXd& I, double, double, bool) {
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;
    G(k,n1) = 1; G(k,n2) = -1;
    G(n1,k) = 1; G(n2,k) = -1;
    I(k) = value;
}

// sinusoidal voltage source
void VoltageSin::addToMatrix(MatrixXd &matrix) {}

void VoltageSin::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;
    double v = vOffset + vAmp * sin(2 * M_PI * freq * t);
    G(k,n1) = 1; G(k,n2) = -1; G(n1,k) = 1; G(n2,k) = -1;
    I(k) = v;
}

void VoltageSin::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx(), k = currentIdx;
    G(k,n1) = 1; G(k,n2) = -1; G(n1,k) = 1; G(n2,k) = -1;
    I(k) = vOffset; // fallback to DC offset
}

// inductors
void Inductor::addToMatrix(MatrixXd &matrix) {}

double Inductor::getCurrent() {
    return cachedCurrent;
}

void Inductor::stampDC(MatrixXd& G, VectorXd& I){ /* short in DC */ }

void Inductor::stampTransient(MatrixXd& G, VectorXd& I,double dt,double, bool) {
    double R=dt/value;
    int n1=node1->getIdx(),n2=node2->getIdx(),k=currentIdx;
    G(k,n1)=1; G(k,n2)=-1; G(n1,k)=1; G(n2,k)=-1; G(k,k)=-R;
    I(k) = -R*prevCurrent;
}

void Inductor::postStepUpdate(double dt){ lastDt=dt; prevCurrent=cachedCurrent; }

// dc current source
void CurrentSource::addToMatrix(MatrixXd &matrix) {}

void CurrentSource::stampDC(MatrixXd& G, VectorXd& I) {
    int n1 = node1->getIdx(), n2 = node2->getIdx();
    I(n1) -= value;
    I(n2) += value;
}

void CurrentSource::stampTransient(MatrixXd& G, VectorXd& I, double dt, double t, bool first) {
    stampDC(G, I);
}

// diodes
void Diode::addToMatrix(MatrixXd &matrix) {}

double Diode::getCurrent() {
    return cachedCurrent;
}

void Diode::stampDC(MatrixXd&, VectorXd&) {}

void Diode::stampTransient(MatrixXd&, VectorXd&, double, double, bool) {}

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

// voltage controlled voltage source
VCVS::VCVS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain)
    : Element(name, n1, n2, gain), controlNode1(ctrlN1), controlNode2(ctrlN2), gain(gain) {}

void VCVS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for VCVS
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

void Circuit::analyseTRAN(double dt,double tStop,double tStart){
    if(!solver){ solver=new Solver(this); solver->freeze(); }
    Solver::Opt o{Solver::Mode::TRAN,dt,tStart};
    for(double t=tStart; t<=tStop; t+=dt){
        o.t=t;
        const auto& x = solver->solveOnce(o);
        results.emplace_back(t,x);
        for(auto *e:getElements()) e->postStepUpdate(dt);
    }
}
VectorXd Circuit::analyseDC(){
    if(!solver){ solver=new Solver(this); solver->freeze(); }
    const auto& x = solver->solveOnce({Solver::Mode::DC});
    return x;
}



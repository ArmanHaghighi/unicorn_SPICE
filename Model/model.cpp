//
// Created by Arman on 5/27/2025.
//

#include "model.h"
#include "solver.h"

bool Circuit::checkElementNameExistence(const string& name) const {
    for (auto el:elements) {
        if (el->getName()==name) {
            return true;
        }
    }
    return false;
}
Node* Circuit::checkNodeNameExistence(const string& name) const {
    for (auto n:nodes) {
        if (n->getName()==name) {
            return n;
        }
    }
    return nullptr;
}

void Circuit::

addElement(Element *element) {
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

string Element::getName() {
    return name;
}

void Ground::makeNode() {
    const string n = getName().erase(getName().size()-5);
    this->~Ground();
    new(this) Node(n);
}

string Ground::getName() {
    return Node::getName()+"(gnd)";
}

void Resistor::addToMatrix(MatrixXd &matrix) {
}

void Resistor::stampDC(MatrixXd& G, VectorXd& I) {
    double g = 1.0 / value;
    int n1 = node1->idx, n2 = node2->idx;
    G(n1,n1) += g; G(n2,n2) += g; G(n1,n2) -= g; G(n2,n1) -= g;
}
void Resistor::stampTransient(MatrixXd& G, VectorXd& I,double, double, bool) {
    stampDC(G,I);
}

void Capacitor::addToMatrix(MatrixXd &matrix) {}

double Capacitor::getCurrent() {}

void Capacitor::stampDC(MatrixXd&, VectorXd&) { /* open in DC */ }
void Capacitor::stampTransient(MatrixXd& G, VectorXd& I,double dt,double, bool first) {
    double GC = value/dt;
    int n1=node1->idx, n2=node2->idx;
    G(n1,n1)+=GC; G(n2,n2)+=GC; G(n1,n2)-=GC; G(n2,n1)-=GC;
    double Ieq = GC * prevVoltage;
    I(n1)-=Ieq; I(n2)+=Ieq;
    cachedCurrent = value*(node1->getVoltage()-node2->getVoltage()-prevVoltage)/dt;
}
void Capacitor::postStepUpdate(double dt){ lastDt=dt; prevVoltage=node1->getVoltage()-node2->getVoltage(); }

void VoltageSource::addToMatrix(MatrixXd &matrix) {}

void VoltageSource::stampDC(MatrixXd& G, VectorXd& I) {
    int n1=node1->idx,n2=node2->idx,k=currentIdx;
    G(k,n1)=1; G(k,n2)=-1; G(n1,k)=1; G(n2,k)=-1;
    I(k)=value;
}
void VoltageSource::stampTransient(MatrixXd& G, VectorXd& I,double,double,bool f){ stampDC(G,I); }

void VoltageSin::addToMatrix(MatrixXd &matrix) {}

void Inductor::addToMatrix(MatrixXd &matrix) {}

double Inductor::getCurrent() {}

void Inductor::stampDC(MatrixXd& G, VectorXd& I){ /* short in DC */ }
void Inductor::stampTransient(MatrixXd& G, VectorXd& I,double dt,double, bool) {
    double R=dt/value;
    int n1=node1->idx,n2=node2->idx,k=currentIdx;
    G(k,n1)=1; G(k,n2)=-1; G(n1,k)=1; G(n2,k)=-1; G(k,k)=-R;
    I(k) = -R*prevCurrent;
}
void Inductor::postStepUpdate(double dt){ lastDt=dt; prevCurrent=cachedCurrent; }

void CurrentSource::addToMatrix(MatrixXd &matrix) {}

void Diode::addToMatrix(MatrixXd &matrix) {}

double Diode::getCurrent() {}

void Zener::addToMatrix(MatrixXd &matrix) {
}

double Zener::getCurrent() {
}

CCVS::CCVS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain)
    : Element(name, n1, n2, gain), controllingElement(ctrlElem), gain(gain) {}

void CCVS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for CCVS
}

double CCVS::getCurrent() {
    return node1->KCL_CurrentCalc(this);
}

CCCS::CCCS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain)
    : Element(name, n1, n2, gain), controllingElement(ctrlElem), gain(gain) {}

void CCCS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for CCCS
}

double CCCS::getCurrent() {
    return gain * controllingElement->getCurrent();
}

VCCS::VCCS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain)
    : Element(name, n1, n2, gain), controlNode1(ctrlN1), controlNode2(ctrlN2), gain(gain) {}

void VCCS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for VCCS
}

double VCCS::getCurrent() {
    return gain * (controlNode1->getVoltage() - controlNode2->getVoltage());
}

VCVS::VCVS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain)
    : Element(name, n1, n2, gain), controlNode1(ctrlN1), controlNode2(ctrlN2), gain(gain) {}

void VCVS::addToMatrix(MatrixXd &matrix) {
    // TODO: Implement MNA for VCVS
}

double VCVS::getCurrent() {
    return node1->KCL_CurrentCalc(this);
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



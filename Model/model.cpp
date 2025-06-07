//
// Created by Arman on 5/27/2025.
//

#include "model.h"

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

double Node::KCL_CurrentCalc(Element *element) {
    return 0;//just to build successfully
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

void Capacitor::addToMatrix(MatrixXd &matrix) {}

double Capacitor::getCurrent() {}

void VoltageSource::addToMatrix(MatrixXd &matrix) {}

void VoltageSin::addToMatrix(MatrixXd &matrix) {}

void Inductor::addToMatrix(MatrixXd &matrix) {}

double Inductor::getCurrent() {}

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



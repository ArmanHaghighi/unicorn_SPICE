//
// Created by Arman on 5/27/2025.
//

#include "model.h"

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

string Element::getName() {
    return name;
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


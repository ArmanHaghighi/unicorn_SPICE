#pragma once
#include "../Controller/controller.h"
#include "../view/view.h"
#include  <bits/stdc++.h>
#include <Eigen/Eigen>
#ifndef MODEL_H
#define MODEL_H

using namespace std;
using namespace Eigen;
class Node;
class Element;

class Circuit {
private:
    list<Element*> elements;
    list<Node*> nodes;
    MatrixXd conductanceMatrix;
public:
    void addElement(Element* element);
    void removeElement(Element* element);
    MatrixXd getMatrix();
    void analyse(string type);
};


class Node {
private:
    int id;
    double voltage;
    list<pair<Element*, double>> elements; //elemets connected to node and their currents
public:
    explicit Node(int id);
    void connectElement(Element* element);
    void removeElement(Element* element);
    double KCL_CurrentCalc(Element* element);
    double getVoltage();
};
class Element {
private:
    string name;
protected:
    vector<Node*> nodes; // nodes of the element (can be replaced with node1* and node2* for elements with only 2 legs)
    double value;
public:
    virtual ~Element() = default;

    virtual void addToMatrix (MatrixXd& matrix)=0;
    virtual double getCurrent()=0;
};

class Resistor : public Element {
public:
    void addToMatrix  (MatrixXd& matrix) override{};//add resistor to circuit matrix
    double getCurrent() override {
        return (nodes[0]->getVoltage()-nodes[1]->getVoltage())/value;
    };// caclulate the currnt passing through rsistor
};
class Capacitor : public Element {
public:
    void addToMatrix(MatrixXd &matrix) override{};//add resistor to circuit matrix
    double getCurrent() override{};// caclulate the currnt passing through rsistor
};

class VoltageSource : public Element {
public:
    void addToMatrix(MatrixXd &matrix) override{};//add resistor to circuit matrix
    double getCurrent() override{//calculate current passing through voltage source
        //using kcl in one of the nodes
        return nodes[0]->KCL_CurrentCalc(this);
    };
};
class Inductor : public Element {
public:
    void addToMatrix(MatrixXd &matrix) override{};//add resistor to circuit matrix
    double getCurrent() override{};// caclulate the currnt passing through rsistor
};
class CurrentSource : public Element {
public:
    void addToMatrix(MatrixXd &matrix) override{};
    double getCurrent() override{};
};


#endif //MODEL_H

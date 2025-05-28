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
    string name;
    list<pair<Element*, double>> elements; //elemets connected to node and their currents
//so that we can change the voltage for a ground
protected:
        double voltage;
public:
    explicit Node(int id);
    void connectElement(Element* element);
    void removeElement(Element* element);
    double KCL_CurrentCalc(Element* element);
    double getVoltage();
    void setVoltage(double v){
        voltage = v;
    }
    list<pair<Element*, double>> returnConnectedElements();
};

class Element {
private:
    string name;
protected:
    Node* node1;
    Node* node2;
    double value;
public:
    virtual ~Element() = default;

    virtual void addToMatrix (MatrixXd& matrix)=0;
    virtual double getCurrent()=0;
};

class ground : public Node {
public:
    explicit ground(int id) : Node(id) {
        setVoltage(0.0);
    }
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
class Diode : public Element {
public:
    string model;
    void addToMatrix(MatrixXd &matrix) override{};
    double getCurrent() override{};
};

#endif //MODEL_H

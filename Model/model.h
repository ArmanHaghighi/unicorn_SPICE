#pragma once
#include  <bits/stdc++.h>
#include <Eigen/Eigen>

#include "model.h"
#ifndef MODEL_H
#define MODEL_H

using namespace std;
using namespace Eigen;
class Node;
class Element;

class Circuit {
private:
    set<Element*> elements;
    set<Node*> nodes;
    MatrixXd conductanceMatrix;
public:
    bool checkElementNameExistence(const string &name) const;

    Node* checkNodeNameExistence(const string &name) const;

    void addElement(Element* element);
    void removeElement(Element* element);
    void removeNode(Node* node);
    MatrixXd getMatrix();
    void analyse(string type);// probably needs to be a class itself
    set<Node*> getNodes();
    set<Element*> getElements();
};

class Node {
private:
    string name;
    map<Element*,optional<double>> elements; //elemets connected to node (and their currents?)
//so that we can change the voltage for a ground
protected:
    double voltage;
public:
    virtual string getName() ;
    explicit Node(const string &name):name(name){}
    void connectElement(Element* element);
    bool removeElement(Element* element);
    double KCL_CurrentCalc(Element* element);
    double getVoltage();
    void setVoltage(double v){
        voltage = v;
    }
    void renameNode(string name);
    map<Element*, double> returnConnectedElements();
    void makeGround();
};

class Element {
private:
    string name;
protected:
    double value;
public:
    string getName();
    Node* node1;
    Node* node2;
    virtual ~Element() = default;
    Element(string name,Node* node1,Node* node2, double value):name(std::move(name)),node1(node1),node2(node2),value(value){}
    virtual void addToMatrix (MatrixXd& matrix)=0;
    virtual double getCurrent()=0;
};

class Ground : public Node {
public:
    void makeNode();
    string getName() override;
    explicit Ground(const string &id) : Node(id) {
        setVoltage(0.0);
    }
};

class Resistor : public Element {
public:
    using Element::Element;//----Inheriting the constructor from Element.
    void addToMatrix  (MatrixXd& matrix) override;;//add resistor to circuit matrix
    double getCurrent() override {
        return (node1->getVoltage()-node2->getVoltage())/value;
    };// calculate the current passing through resistor
};
class Capacitor : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override;;// calculate the current passing through resistor
};

class VoltageSource : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override{//calculate current passing through voltage source
        //using kcl in one of the nodes
        return node1->KCL_CurrentCalc(this);
    };
};

class VoltageSin : public Element {
    double vOffset;
    double vAmp;
    double freq;
public:
    VoltageSin(string name,Node* n1,Node* n2,double vOffset,double vAmp,double freq):Element(name,n1,n2,vAmp/sqrt(2)),vAmp(vAmp),vOffset(vOffset),freq(freq){}
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override{//calculate current passing through voltage source
        //using kcl in one of the nodes
        return node1->KCL_CurrentCalc(this);
    };
};
class Inductor : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override;;// caclulate the currnt passing through rsistor
};
class CurrentSource : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;
    double getCurrent() override {
        return value;
    };
};
class Diode : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;
    double getCurrent() override;;
};


class Zener  : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;
    double getCurrent() override;;
};

class CCVS : public Element {
    Element* controllingElement;
    double gain; //Ohms
public:
    CCVS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain);
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    Element* getControllingElement() const {
        return controllingElement;
    }
    double getGain() const {
        return gain;
    }
};

class CCCS : public Element {
    Element* controllingElement;
    double gain; //no unit
public:
    CCCS(string name, Node* n1, Node* n2, Element* ctrlElem, double gain);
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    Element* getControllingElement() const {
        return controllingElement;
    }
    double getGain() const {
        return gain;
    }
};

class VCCS : public Element {
    Node* controlNode1; //positive
    Node* controlNode2; //negative
    double gain; //siemens
public:
    VCCS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain);
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    Node* getControlNode1() const {
        return controlNode1;
    }
    Node* getControlNode2() const {
        return controlNode2;
    }
    double getGain() const {
        return gain;
    }
};

class VCVS : public Element {
    Node* controlNode1; //positive
    Node* controlNode2; //negative
    double gain; //no unit
public:
    VCVS(string name, Node* n1, Node* n2, Node* ctrlN1, Node* ctrlN2, double gain);
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    Node* getControlNode1() const {
        return controlNode1;
    }
    Node* getControlNode2() const {
        return controlNode2;
    }
    double getGain() const {
        return gain;
    }
};
#endif //MODEL_H

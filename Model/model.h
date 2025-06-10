#pragma once
#include  <bits/stdc++.h>
#include <Eigen/Eigen>
#include "solver.h"

//#include "model.h"
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
    Solver* solver{nullptr};
    vector<pair<double,VectorXd>> results;
    VectorXd currentVector;
public:
    virtual ~Circuit() = default;
    Circuit() {
        solver =new Solver(this);
    }
    Element* checkElementNameExistence(const string &name) const;
    const auto& getResults() const { return results; }
    const auto& getCurrentVector() const { return currentVector; }
    virtual void initializeCurrentVector();
    virtual void initializeConductanceMatrix();
    void analyseTRAN(double step,double stop,double start=0);
    VectorXd analyseDC();
    // virtual bool checkElementNameExistence(const string& name);
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
    map<Element*,optional<double>> elements; //elements connected to node (and their currents?)
//so that we can change the voltage for a ground
protected:
    double voltage;
public:
    int idx;
    virtual string getName() ;
    virtual int getIdx() const {
        return idx;
    }
    explicit Node(const string &name,int idx=-1):name(name),idx(idx){}
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
protected:
    double value;
    string name;
public:
    int currentIdx{0};
    string getName();
    Node* node1;
    Node* node2;
    virtual ~Element() = default;
    Element(string name,Node* node1,Node* node2, double value):name(std::move(name)),node1(node1),node2(node2),value(value){}
    virtual bool usesBranchCurrent() const { return false; }
    // stamping API (DC & Transient)
    virtual void stampDC(Eigen::MatrixXd&, Eigen::VectorXd&) = 0;
    virtual void stampTransient(Eigen::MatrixXd&, Eigen::VectorXd&, double dt, double t, bool first) = 0;
    virtual void postStepUpdate(double /*dt*/) {} //for capacitors and inductors
    virtual void setSourceValue(double /*v*/) {}
    //virtual void addToMatrix (MatrixXd& matrix)=0;
    //virtual double getCurrent()=0;
    virtual void addToMatrix(Eigen::MatrixXd& G)  {
        static Eigen::VectorXd dummy;               // resized on demand
        if (dummy.size() != G.rows()) dummy = Eigen::VectorXd::Zero(G.rows());
        else dummy.setZero();
        stampDC(G, dummy);
        }

    virtual double getCurrent() { return cachedCurrent; }
    int getCurrentIdx() const { return currentIdx; }

    mutable double cachedCurrent{};
};

class Ground : public Node {
public:
    int getIdx() const override {
        return 0;
    }
    void makeNode();
    string getName() override;
    explicit Ground(const string &id,int idx) : Node(id,idx) {
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
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
        double dt, double t, bool first) override;

};
class Capacitor : public Element {
public:
    using Element::Element;
    double prevVoltage {0.0};
    double lastDt {1.0};
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override;;// calculate the current passing through
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
    void postStepUpdate(double dt) override;

};

class VoltageSource : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override{//calculate current passing through voltage source
        //using kcl in one of the nodes
        return node1->KCL_CurrentCalc(this);
    };
    bool usesBranchCurrent() const override { return true; }
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
};

class VoltageSin : public Element {
    double vOffset;
    double vAmp;
    double freq;
public:
    VoltageSin(string name,Node* n1,Node* n2,double vOffset,double vAmp,double freq):Element(name,n1,n2,vAmp/sqrt(2)),vAmp(vAmp),vOffset(vOffset),freq(freq){}
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override{//calculate current passing through voltage source
        //using kcl in one of the nodes
        return node1->KCL_CurrentCalc(this);
    }
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                    double dt, double t, bool first) override;
};

class Inductor : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;//add resistor to circuit matrix
    double getCurrent() override;;// calculate the current passing through resistor
    bool usesBranchCurrent() const override { return true; }
    double prevCurrent{}; double lastDt{1};
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
    void postStepUpdate(double dt) override;
};

class CurrentSource : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;;
    double getCurrent() override {
        return value;
    };
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;

    void stampTransient(Eigen::MatrixXd &G, Eigen::VectorXd &I,double dt, double t, bool first) override ;
};

class Diode : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
};

class Zener : public Element {
public:
    using Element::Element;
    void addToMatrix(MatrixXd &matrix) override;
    double getCurrent() override;
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
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
    bool usesBranchCurrent() const override { return true; }
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
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
    bool usesBranchCurrent() const override { return true; }
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
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
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
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
    bool usesBranchCurrent() const override { return true; }
    void stampDC(Eigen::MatrixXd& G, Eigen::VectorXd& I) override;
    void stampTransient(Eigen::MatrixXd& G, Eigen::VectorXd& I,
                        double dt, double t, bool first) override;
};
#endif //MODEL_H
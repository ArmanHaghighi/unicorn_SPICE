//
// Created by Arman on 5/27/2025.
//
#pragma once
#include "../view/view.h"
#include "../Model/model.h"
#include <exception>
#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller{
    string type;
    CLI* cli;
    Circuit* circuit;
public:
    Controller(string type);
    ~Controller();
    void restart();
    void parse(string line);
    void addElement(string type,string name,string n1,string n2 , double value,string model="",bool sin=false,double offset =0, double freq=0,const string& cN1="",const string& cN2="");
    void runTRAN(double step,double stop,double start,const std::vector<std::pair<char,std::string>>& probes);
    void deleteElement(string name,string element);
    void renameNode(string old,string name);
    void listNodes() const;
    void listElements() const;
    void listElementsByType(string type) const;
    void addGnd(string nodeName);
    void deleteGnd(string nodeName);
    void checkGnd();
};



class SPICE_Exception : public std::exception {};

class ParsingException : public SPICE_Exception {
    string parameterName;
    int code;
    string error;
public:
    ParsingException(int code,string parameterName="");
    const char* what() const noexcept override ;
};
class FileExp:public SPICE_Exception {
    public:
    const char* what() const noexcept override ;
};
class CircuitException : public SPICE_Exception {
    protected:
    string thing;
    public:
    CircuitException(string thing):thing(thing){}
};
class ExistExp:public CircuitException {
    public:
    ExistExp(string type,string name):CircuitException(type+' '+name){}
    const char* what() const noexcept override ;
};
class NotFound:public CircuitException {
    using CircuitException::CircuitException;
    public:
    const char* what() const noexcept override ;
};
class NodeNotFound:public CircuitException {
    using CircuitException::CircuitException;

    public:
    const char* what() const noexcept override ;
};
class ControlException:public CircuitException {
    using CircuitException::CircuitException;
    public:
    const char* what() const noexcept override ;
};

class GNDNotFound:public CircuitException {
    public:
        GNDNotFound(): CircuitException("") {
    };
    const char* what() const noexcept override ;
};
class AnalysisException : public SPICE_Exception {

};

#endif //CONTROLLER_H

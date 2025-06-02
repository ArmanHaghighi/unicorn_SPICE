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
private:
    string type;
    CLI* cli;
    Circuit* circuit;
public:
    Controller(string type);
    ~Controller();
    void parse(string line);
    void addElement(string type,string name,string n1,string n2 , double value,string model="",bool sin=false,double offset =0, double freq=0);
    void deleteElement();
    void renameNode();
    void listNodes() const;
    void listElements() const;
    void listElementsByType(string type);
};



class SPICE_Exception : public std::exception {};

class ParsingException : public SPICE_Exception {
    string parameterName;
    int code;
    string errors[4]={"Syntax error", parameterName+" cannot be zero or negative","Element "+parameterName+"not found in library"," Invalid syntax - correct format:\n.rename node <old_name> <new_name>"};
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
class AnalysisException : public SPICE_Exception {

};

#endif //CONTROLLER_H

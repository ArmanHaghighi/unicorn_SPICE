//
// Created by Arman on 5/27/2025.
//
#pragma once
#include "../view/view.h"
#include "../Model/model.h"
#include <exception>
#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller {
private:
    string type;
    CLI* cli;
public:
    Controller(string type);
    ~Controller();
    void parse(string line);
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
class CircuitException : public SPICE_Exception {

};
class AnalysisException : public SPICE_Exception {

};

#endif //CONTROLLER_H

//
// Created by Arman on 5/27/2025.
//
#pragma once
#include "../view/view.h"
#include "../Model/model.h"
#include <exception>
#ifndef CONTROLLER_H
#define CONTROLLER_H
class SPICE_Exception : public std::exception {};

class ParsingException : public SPICE_Exception {

};
class CircuitException : public SPICE_Exception {

};
class AnalysisException : public SPICE_Exception {

};

#endif //CONTROLLER_H

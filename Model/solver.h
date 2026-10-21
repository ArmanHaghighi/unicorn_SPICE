//
// Created by Latitude 5420 on 2025-06-07.
//

#ifndef SOLVER_H
#define SOLVER_H

#pragma once
#include <Eigen/Eigen>

using namespace Eigen;

class Circuit;

class Solver {
public:
    Circuit* ckt;
    MatrixXd G;
    VectorXd RHS, sol;
    enum class Mode { DC, TRAN };
    bool firstStep = true;
    struct Opt {
        Mode mode{Mode::DC};
        double dt{0};// for transient analysis
        double t{0};// for transient analysis
    };
    explicit Solver(Circuit* c) : ckt(c) {}
    void freeze();
    const VectorXd& solveOnce(const Opt&);
    void resizeMatrix();
};

#endif //SOLVER_H

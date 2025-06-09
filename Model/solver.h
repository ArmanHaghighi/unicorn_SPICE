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
    Circuit* ckt;
    MatrixXd G;
    VectorXd RHS, sol;
public:
    enum class Mode { DC, TRAN };
    struct Opt {
        Mode mode{Mode::DC};
        double dt{0};// for transient analysis
        double t{0};// for transient analysis
    };
    explicit Solver(Circuit* c) : ckt(c) {}
    void freeze();// assign indices & size G/RHS
    const VectorXd& solveOnce(const Opt&);
};

#endif //SOLVER_H

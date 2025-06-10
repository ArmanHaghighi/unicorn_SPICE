//
// Created by Latitude 5420 on 2025-06-07.
//

#include "solver.h"
#include "model.h"

using namespace Eigen;
using namespace std;

void Solver::freeze() {
    int next = 0;
    for (auto *n : ckt->getNodes()) {
        if (dynamic_cast<Ground*>(n))
            n->idx=0;
    }
    for (auto *n : ckt->getNodes()) {
        if (n->idx == -1) {
            n->idx = next++;
        }
    }
    for (auto *e : ckt->getElements()) {
        if (e->usesBranchCurrent()) {
            std::cout << "Assigning currentIdx to element " << e->getName() << std::endl;
            e->currentIdx = next++;
        }
    }
    resizeMatrix();
    G.setZero();
    RHS.setZero();
}

const VectorXd& Solver::solveOnce(const Opt& o) {
    G.setZero();
    RHS.setZero();

    std::cout << "\n--- solveOnce t=" << o.t
              << " mode=" << (o.mode==Mode::DC?"DC":"TRAN") << " ---\n"; // temp

    for (auto *el : ckt->getElements()) {
        if (o.mode == Mode::DC)
            el->stampDC(G, RHS);
        else
            el->stampTransient(G, RHS, o.dt, o.t, o.t == 0);
    }

    std::cout << "G =\n" << G << "\nRHS = " << RHS.transpose() << "\n\n"; // temp

    try {
        sol = G.fullPivLu().solve(RHS);
    } catch (const std::exception& e) {
        std::cerr << "Matrix solve failed: " << e.what() << std::endl;
        throw std::runtime_error("Matrix solve failed");
    }

    int nVars = sol.size();
    for (auto *n : ckt->getNodes()) {
        int idx = n->getIdx();
        if (idx >= 0 && idx < nVars)
            n->setVoltage(sol(idx));
    }

    for (auto *e : ckt->getElements()) {
        if (e->usesBranchCurrent()) {
            int idx = e->currentIdx;
            if (idx >= 0 && idx < nVars)
                e->cachedCurrent = sol(idx);
        }
    }

    if (o.mode == Mode::TRAN) {
        for (auto *e : ckt->getElements())
            e->postStepUpdate(o.dt);
    }

    return sol;
}


void Solver::resizeMatrix() {
    int max_idx = 0;
    if (!ckt) {
        cerr << "Error: Circuit (ckt) is not initialized!" << endl;
        return;
    }
    for (auto* n : ckt->getNodes()) {
        if (n == nullptr) {
            std::cerr << "Error: Found nullptr in the node set!" << std::endl;
            continue;
        }

        max_idx = std::max(max_idx, n->getIdx());
    }

    G.resize(max_idx + 1, max_idx + 1);
    RHS.resize(max_idx + 1);

    cout << "Resized G to " << G.rows() << "x" << G.cols() << endl;
}



//
// Created by Latitude 5420 on 2025-06-07.
//

#include "solver.h"
#include "model.h"

using namespace Eigen;
using namespace std;

void Solver::freeze() {
    int next = 1;
    for (auto *n : ckt->getNodes())
        if (!dynamic_cast<Ground*>(n)) n->idx = next++;
    for (auto *e : ckt->getElements())
        if (e->usesBranchCurrent())   e->currentIdx = next++;
    G.resize(next, next);
    RHS.resize(next);
}

const VectorXd& Solver::solveOnce(const Opt& o) {
    G.setZero();
    RHS.setZero();

    for (auto *el : ckt->getElements()) {
        if (o.mode == Mode::DC)
            el->stampDC(G, RHS);
        else
            el->stampTransient(G, RHS, o.dt, o.t, o.t == 0);
    }

    sol = G.fullPivLu().solve(RHS);

    // Safe copying of voltages
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

    return sol;
}

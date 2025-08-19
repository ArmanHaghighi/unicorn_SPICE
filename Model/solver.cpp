//
// Created by Latitude 5420 on 2025-06-07.
//

#include "solver.h"
#include "model.h"

using namespace Eigen;
using namespace std;

// solver.cpp

void Solver::freeze() {
    int next = 0;
    bool hasGround = false;

    // 1) Ensure grounds are index 0, and reindex non-grounds from scratch
    for (auto *n : ckt->getNodes()) {
        if (dynamic_cast<Ground*>(n)) {
            n->idx = 0;
            hasGround = true;
        } else {
            n->idx = -1; // force reindex of all non-ground nodes
        }
    }

    next = hasGround ? 1 : 0;

    // 2) Assign node indices densely
    for (auto *n : ckt->getNodes()) {
        if (!dynamic_cast<Ground*>(n) && n->idx == -1) {
            n->idx = next++;
        }
    }

    // 3) Assign branch current indices (for elements that require them)
    for (auto *e : ckt->getElements()) {
        if (e->usesBranchCurrent()) {
            e->currentIdx = next++;
        } else {
            e->currentIdx = -1;
        }
    }

    resizeMatrix();
    G.setZero();
    RHS.setZero();
}

const VectorXd& Solver::solveOnce(const Opt& o) {
    G.setZero();
    RHS.setZero();

    for (auto *el : ckt->getElements()) {
        if (o.mode == Mode::DC) {
            el->stampDC(G, RHS);
        } else {
            el->stampTransient(G, RHS, o.dt, o.t, o.first);
        }
    }

    try {
        sol = G.fullPivLu().solve(RHS);
    } catch (const std::exception& e) {
        std::cerr << "Matrix solve failed: " << e.what() << std::endl;
        throw std::runtime_error("Matrix solve failed");
    }

    int nVars = sol.size();

    // Update node voltages
    for (auto *n : ckt->getNodes()) {
        int idx = n->getIdx();
        if (idx >= 0 && idx < nVars)
            n->setVoltage(sol(idx));
    }

    // Update element branch currents
    for (auto *e : ckt->getElements()) {
        if (e->usesBranchCurrent()) {
            int idx = e->currentIdx;
            if (idx >= 0 && idx < nVars)
                e->cachedCurrent = sol(idx);
        }
    }

    return sol;
}

void Solver::resizeMatrix() {
    if (!ckt) {
        std::cerr << "Error: Circuit (ckt) is not initialized!" << std::endl;
        return;
    }

    int max_idx = -1;

    // Consider node indices
    for (auto* n : ckt->getNodes()) {
        if (n == nullptr) {
            std::cerr << "Error: Found nullptr in the node set!" << std::endl;
            continue;
        }
        max_idx = std::max(max_idx, n->getIdx());
    }

    // Consider branch current indices as well
    for (auto* e : ckt->getElements()) {
        if (e && e->usesBranchCurrent())
            max_idx = std::max(max_idx, e->currentIdx);
    }

    int size = std::max(0, max_idx + 1);
    G.resize(size, size);
    RHS.resize(size);
}



//
// Created by Latitude 5420 on 2025-08-26.
//

#include "Netlister.h"
#include "wire.h"
#include "elements.h"
#include "Model/model.h"
#include <QSet>
using namespace Spice;

struct DSU {
    QHash<Spice::Node*, Spice::Node*> p;
    Spice::Node* f(Spice::Node* x){ if (!p.contains(x) || p[x]==x) return p[x]=x; return p[x]=f(p[x]); }
    void u(Spice::Node* a, Spice::Node* b){ a=f(a); b=f(b); if (a!=b) p[b]=a; }
};

NetlistResult Netlister::build(QGraphicsScene* scene) {
    DSU dsu;
    // init parents for all element pins
    for (auto* item : scene->items()) {
        if (auto* e = qgraphicsitem_cast<Element*>(item)) {
            //for (auto* pin : e->getNodes()) dsu.p[pin]=pin;
        }
    }
    // union by wires
    for (auto* item : scene->items()) {
        if (auto* w = qgraphicsitem_cast<Wire*>(item)) {
            dsu.u(w->startNode(), w->endNode());
        }
    }
    QHash<Spice::Node*, QString> repName; int next=1;
    NetlistResult r;
    for (auto it = dsu.p.begin(); it != dsu.p.end(); ++it) {
        Spice::Node* rep = dsu.f(it.key());
        //if (!repName.contains(rep)) repName[rep] = QString("N%1").arg(next++);
        //r.nodeToNet[it.key()] = repName[rep];
    }
    return r;
}

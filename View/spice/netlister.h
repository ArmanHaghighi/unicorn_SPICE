//
// Created by Latitude 5420 on 2025-08-26.
//

#pragma once
#include <QObject>
#include <QGraphicsScene>
#include <QHash>
#include <QString>

class Node; // your graphics pin

struct NetlistResult {
    QHash<Node*, QString> nodeToNet;     // each graphics pin → net name
};

class Netlister {
public:
    static NetlistResult build(QGraphicsScene* scene);
};

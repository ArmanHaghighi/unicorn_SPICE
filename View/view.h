//
// Created by Arman on 5/27/2025.
//
#pragma once
// #include "../Controller/controller.h"
// #include "../Model/model.h"
#include <bits/stdc++.h>
using namespace std;

class CLI {
    string line;

public:
    CLI();
public:
    void prompt(string line);
    static double parseNumber(string n);
};

#ifndef VIEW_H
#define VIEW_H

#endif //VIEW_H

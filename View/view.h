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
    vector<filesystem::path> files;
public:
    CLI();
public:
    void prompt(string line);
    static double parseNumber(string n);

    void openFile(int n);

    void fileMenu();
    int showFileMenu();
};

#ifndef VIEW_H
#define VIEW_H

#endif //VIEW_H

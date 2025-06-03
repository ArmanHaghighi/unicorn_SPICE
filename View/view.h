//
// Created by Arman on 5/27/2025.
//
#pragma once
#include <bits/stdc++.h>

class Controller;
using namespace std;
class CLI {
    Controller* controller;
    string line;
    vector<filesystem::path> files;
    ofstream fout;
public:
    CLI(Controller* controller);
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

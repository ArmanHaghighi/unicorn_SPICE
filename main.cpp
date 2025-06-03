#include <bits/stdc++.h>

#include "Controller/controller.h"
// #include "view/view.h"
// #include "model/model.h"
using namespace std;
int main() {
    string line;
    Controller CliController("CLI");
    while (getline(cin,line)) {
        CliController.parse(line);
    }
    return 0;
}


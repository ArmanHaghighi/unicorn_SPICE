#include <bits/stdc++.h>

#include "Controller/controller.h"
// #include "view/view.h"
// #include "model/model.h"
#include "View/spice/mainwindow.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    string line;
    Controller CliController("CLI");
    while (getline(cin,line)) {
        CliController.parse(line);
    }
    return a.exec();
}


#include <bits/stdc++.h>

#include "Controller/controller.h"
#include "view/view.h"
#include "model/model.h"
#include "View/spice/mainwindow.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[]) {
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        cout<<w.isVisible();
        return a.exec();
    }
    catch (const std::exception& e) {
        cout<<e.what();
        return 1;
    }
    string line;

    // Controller CliController("CLI");
    // while (true) {
    //     while (getline(cin,line)) {
    //         CliController.parse(line);
    //     }
    // }

}


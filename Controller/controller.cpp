//
// Created by Arman on 5/27/2025.
//

#include "controller.h"

Controller::Controller(string type) {
    this->type = type;
    if (type=="CLI") {
        cli=new CLI();
    }
}
Controller::~Controller() {
    delete cli;
}
void Controller::parse(string line) {
        try {
            cli->prompt(line);
        }
        catch(ParsingException &e) {
            cerr << e.what() << endl;
        }

}


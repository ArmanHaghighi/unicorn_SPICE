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
        cout << e.what() << endl;
    }
    cout<<">>";
}

ParsingException::ParsingException(int code, string parameterName):code(code){
    this->parameterName=parameterName;
}

const char *ParsingException::what() const noexcept {
    return ("Error: "+errors[code]).c_str();
}


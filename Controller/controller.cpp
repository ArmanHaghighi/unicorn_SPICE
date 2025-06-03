//
// Created by Arman on 5/27/2025.
//

#include "controller.h"

Controller::Controller(string type) {
    this->type = type;
    circuit=new Circuit();
    if (type=="CLI") {
        cli=new CLI(this);
    }
}

Controller::~Controller() {
    delete cli;
    delete circuit;
}

void Controller::restart() {
    delete circuit;
    circuit=new Circuit();
}

void Controller::parse(string line) {
    try {
        cli->prompt(line);
    }
    catch(SPICE_Exception &e) {
        cout << e.what() << endl;
    }
    cout<<">>";
}

void Controller::addElement( string type ,string name, string n1, string n2, double value, string model ,bool sin,double offset , double freq) {
    if (circuit->checkElementNameExistence(name))
        throw ExistExp(type,name);
    Node* node1,*node2;
    if (!((node1= circuit->checkNodeNameExistence(n1))))
        node1 =new Node(n1);
    if (!((node2= circuit->checkNodeNameExistence(n2))))
        node2 =new Node(n2);
    Element*e = nullptr;
    switch (name[0]) {
        case 'R':
            e=new Resistor(name,node1,node2,value);
            break;
        case 'C':
            e=new Capacitor(name,node1,node2,value);
            break;
        case 'L':
            e=new Inductor(name,node1,node2,value);
            break;
        case 'D':
            if (model != "D" && model != "Z") {
                throw ParsingException(2, "Diode model: " + model);
            }
            e=new Diode(name,node1,node2,model);
            break;
        case'V':
            if (!sin)
                e=new VoltageSource(name,node1,node2,value);
            else
                e=new VoltageSin(name,node1,node2,offset,value,freq);

            break;
        case 'I':
            e=new CurrentSource(name,node1,node2,value);
            break;

        default:
            break;
    }
    if (e)
        circuit->addElement(e);
    else{
        delete e;
        delete node1;
        delete node2;
        throw ParsingException(2,name);
    }
}

void Controller::listNodes() const {
    string s;
    cout<<"Available nodes:"<<endl;
    for (Node* n:circuit->getNodes()) {
        s.append(n->getName()+", ");
    }
    s.pop_back();
    s.pop_back();
    cout<<s<<endl;
}

void Controller::listElements() const {
    string s;
    for (Element* e:circuit->getElements()) {
        s.append(e->getName()+", ");
    }
    s.pop_back();
    s.pop_back();
    cout<<s<<endl;}

void Controller::listElementsByType(string type) const {
    string s;
    for (Element* e:circuit->getElements()) {
        if (tolower(e->getName()[0])==tolower(type[0]))
            s.append(e->getName()+", ");
    }
    try{
        s.pop_back();
        s.pop_back();
        cout<<s<<endl;
    }catch (...) {
        cout<<"Exception occurred during listing of elements";
        throw;
    }
}


ParsingException::ParsingException(int code, string parameterName):code(code){
    this->parameterName=parameterName;
}

const char *ParsingException::what() const noexcept {
    return ("Error: "+errors[code]).c_str();
}

const char * FileExp::what() const noexcept {
    return ("Cannot open file-File not found or is not a valid txt file");
}

const char * ExistExp::what() const noexcept {
    return ("Error: "+thing+" already exists in the circuit").c_str();
}

const char * NotFound::what() const noexcept {
    return (thing+"not found in circuit").c_str();
}


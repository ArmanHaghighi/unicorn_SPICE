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

void Controller::addElement( string type ,string name, string n1, string n2, double value, string model , const bool sin, const double offset , double freq,const string& cN1,const string& cN2) {
    if (circuit->checkElementNameExistence(name))
        throw ExistExp(type,name);
    Node* node1,*node2,*ctrlNode1,*ctrlNode2;
    if (!((node1= circuit->checkNodeNameExistence(n1))))
        node1 =new Node(n1);
    if (!((node2= circuit->checkNodeNameExistence(n2))))
        node2 =new Node(n2);
    ctrlNode1=circuit->checkNodeNameExistence(cN1);
    ctrlNode2=circuit->checkNodeNameExistence(cN2);
    Element* ctrlElement=circuit->checkElementNameExistence(cN1);
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
            if (model == "D") {
                e=new Diode(name,node1,node2,0);
            }
            else if (model == "Z") {
                e=new Zener(name,node1,node2,0.7);
            }
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
        case 'E':
            if (!ctrlNode1) {
                throw ControlException(cN1);
            }
            if (!ctrlNode2) {
                throw ControlException(cN2);
            }
             e=new VCVS(name,node1,node2,ctrlNode1,ctrlNode2,value);
            break;
        case 'F':
            if (!ctrlNode1) {
                throw ControlException(cN1);
            }
            e=new CCCS(name,node1,node2,ctrlElement,value);
            break;
        case 'G':
            if (!ctrlNode1) {
                throw ControlException(cN1);
            }
            if (!ctrlNode2) {
                throw ControlException(cN2);
            }
            e=new VCCS(name,node1,node2,ctrlNode1,ctrlNode2,value);
            break;
        case 'H':
            if (!ctrlNode1) {
                throw ControlException(cN1);
            }
            e=new CCVS(name,node1,node2,ctrlElement,value);
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

void Controller::deleteElement(string name,string element) {
    Element* elm=nullptr;
    for (auto e:circuit->getElements()) {
        if (e->getName() == name)
            elm=e;
    }
    if (!elm)
        throw NotFound(element);
    circuit->removeElement(elm);
}

void Controller::renameNode(string old, string name) {
    Node* oldNode=nullptr;
    for (auto n:circuit->getNodes()) {
        if (n->getName() == old)
            oldNode=n;
        if (n->getName() == name)
            throw ExistExp("Node",name);
    }
    if (!oldNode)
        throw NodeNotFound(old);
    oldNode->renameNode(name );
    cout<<"SUCCESS: Node renamed from "<<old<<" to "<<name<<endl;
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

void Controller::addGnd(string nodeName) {
     Node* node=nullptr;
    for (const auto &n:circuit->getNodes()) {
        string name = n->getName();
        if (name == nodeName)
            node=n;
        if (name.length()>5&& name.substr(name.size()-5) == "(gnd)")
            throw ExistExp("a ground as ",name);

    }
    if (!node)
        throw NodeNotFound(nodeName);
    node->makeGround();
}

void Controller::deleteGnd(string nodeName) {
    Node *node = nullptr;
    for (const auto &n:circuit->getNodes()) {
        string name = n->getName();
        if (name == nodeName+"(gnd)")
            node=n;
        // if (name.length()>5&& name.substr(name.size()-5) == "(gnd)")
        //     throw NodeNotFound("ground as " +nodeName);

    }
    if (!node)
        throw NodeNotFound("a ground as" +nodeName);
    try {
        Ground* gnd=dynamic_cast<Ground*>(node);
        if (!gnd)
            throw 0;
        gnd->makeNode();
    }
    catch (...) {
        cout<<"Node is not a ground\n";
        throw NotFound(nodeName);
    }
}

void Controller::runTRAN(double step,double stop,double start,const vector<pair<char,string>>& probes){
    circuit->analyseTRAN(step,stop,start);
    const auto& res = circuit->getResults();
    for(const auto& [t,x] : res){
        cout<<t;
        for(const auto& p:probes){
            if(p.first=='V'){
                for(auto *n:circuit->getNodes()) if(n->getName()==p.second) cout<<","<<n->getVoltage();
            }else if(p.first=='I'){
                for(auto *e:circuit->getElements()) if(e->getName()==p.second) cout<<","<<e->getCurrent();
            }
        }
        cout<<"\n";
    }
}


ParsingException::ParsingException(int code, string parameterName):code(code) {
    this->parameterName=parameterName;
    switch (code){
        case 0:
            error="Syntax error";
            break;
        case 1:
            error= parameterName+" cannot be zero or negative";
            break;
        case 2:
            error="Element "+parameterName+" not found in library";
            break;
        case 3:
            error=" Invalid syntax - correct format:\n.rename node <old_name> <new_name>";
            break;
        default:
            error="Unknown error";

    }
}

const char *ParsingException::what() const noexcept {
    return ("Error: "+error).c_str();
}

const char * FileExp::what() const noexcept {
    return ("Cannot open file-File not found or is not a valid txt file");
}

const char * ExistExp::what() const noexcept {
    return ("Error: "+thing+" already exists in the circuit").c_str();
}

const char * NotFound::what() const noexcept {
    return ("Error: Cannot delete "+thing+"; not found in circuit").c_str();
}

const char * NodeNotFound::what() const noexcept {
    return ("ERROR: Node "+thing+" does not exist in the circuit").c_str();
}

const char * ControlException::what() const noexcept {
    return ("Error: Dependent source( "+thing+" )has an undefined control parameter.").c_str();

}


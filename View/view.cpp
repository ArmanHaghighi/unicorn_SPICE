//
// Created by Arman on 5/27/2025.
//

#include "view.h"
#include "../Model/CLI_regexes.h"

CLI::CLI(Controller* controller):controller(controller) {
    for (auto d: filesystem::directory_iterator("..\\files")) {
        files.push_back(d.path());
    }
    cout << "<****************--SPICE--****************>" << endl;
    cout << ">>";
}

void CLI::prompt(string line) {
    smatch matches;
    if (regex_match(line, matches, Cli_regexes::RESISTOR_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'R')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        if (value <= 0)
            throw ParsingException(1, "Resistance");
        cout << "added res " << name << ' ' << node1 << ' ' << node2 << ' ' << value << endl;
        controller->addElement("resistor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::RESISTOR_DELETE)) {
    } else if (regex_match(line, matches, Cli_regexes::CAPACITOR_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'C')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        if (value <= 0)
            throw ParsingException(1, "Capacitance");
        cout << "added cap " << name << ' ' << node1 << ' ' << node2 << ' ' << value << endl;
        controller->addElement("capacitor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::CAPACITOR_DELETE)) {
    } else if (regex_match(line, matches, Cli_regexes::INDUCTOR_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'L')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        if (value <= 0)
            throw ParsingException(1, "Inductance");
        cout << "added ind " << name << ' ' << node1 << ' ' << node2 << ' ' << value << endl;
        controller->addElement("inductor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::INDUCTOR_DELETE)) {
    } else if (regex_match(line, matches, Cli_regexes::DIODE_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'D')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string model = matches[4].str();
        cout << "added diod " << name << ' ' << node1 << ' ' << node2 << ' ' << model << endl;
        controller->addElement("diode",name,node1,node2,0,model);
    } else if (regex_match(line, matches, Cli_regexes::DIODE_DELETE)) {
    } else if (regex_match(line, matches, Cli_regexes::GROUND_ADD)) {
        if (matches[1].str() != "GND")
            throw ParsingException(2, matches[1].str());
        string node = matches[2].str();
        //Controller::addGND
    } else if (regex_match(line, matches, Cli_regexes::GROUND_DELETE)) {
        string node = matches[2].str();
        //Controller::addGND
    } else if (regex_match(line, matches, Cli_regexes::VOLTAGE_SOURCE_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        controller->addElement("voltage Source",name,node1,node2,value,name);
    } else if (regex_match(line, matches, Cli_regexes::CURRENT_SOURCE_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        controller->addElement("current Source",name,node1,node2,value,name);
    } else if (regex_match(line, matches, Cli_regexes::SIN_SOURCE_ADD)) {
        // cout << "vsin\n";
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double vOffset = parseNumber(matches[4].str());
        double vAmp = parseNumber(matches[5].str());
        double freq = parseNumber(matches[6].str());
        controller->addElement("sine voltage source",name,node1,node2,vAmp,"",true,vOffset,freq);
    }
    // else   if (regex_match(line,matches,Cli_regexes::PULSE_SOURCE_ADD)) {
    //
    // }
    // else if (regex_match(line, matches, Cli_regexes::VCCS_ADD)) {
    // } else if (regex_match(line, matches, Cli_regexes::VCVS_ADD)) {
    // } else if (regex_match(line, matches, Cli_regexes::CCCS_ADD)) {
    // } else if (regex_match(line, matches, Cli_regexes::CCVS_ADD)) {}
    else if (regex_match(line, matches, Cli_regexes::NODES_LIST)) {
        //Controller::listNodes
    } else if (regex_match(line, matches, Cli_regexes::NODE_RENAME)) {
        if (matches[1].str() != "node" && !matches[2].str().empty() && !matches[3].str().empty())
            throw ParsingException(4);
        //Controller::renameNode
        cout << "SUCCESS: Node renamed from " << matches[2].str() << " to " << matches[3].str() << endl;
    } else if (regex_match(line, matches, Cli_regexes::ELEMENTS_LIST)) {
        if (matches[1].length() > 0) {
            //.list [element]
        } else {
            //.list
        }
    } else if (regex_match(line, matches, Cli_regexes::PRINT_COMMAND)) {
        //costume syntax error command not implemented
        string analysis = matches[1].str();
        if (analysis == "TRAN") {
            double step = parseNumber(matches[2].str());
            double stop = parseNumber(matches[3].str());
            double start = 0, maxStep = 0;
            if (matches[4].matched) {
                start = parseNumber(matches[4].str());
            }
            if (matches[5].matched) {
                maxStep = parseNumber(matches[5].str());
            }
            vector<pair<string, string> > names_params;
            string variables = matches[6].str();
            regex var_regex(R"(([VI])\(([\w\d]+)\))");
            auto vars_begin = sregex_iterator(variables.begin(), variables.end(), var_regex);
            for (auto it = vars_begin; it != std::sregex_iterator(); ++it) {
                names_params.emplace_back((*it)[1].str(), (*it)[2].str());
            }
            //Controller::analyse
        } else if (analysis == "DC") {
            string SourceName = matches[2].str();
            double start = parseNumber(matches[3].str());
            double end = parseNumber(matches[4].str());
            double increment = parseNumber(matches[5].str());

            vector<pair<string, string> > names_params;
            string variables = matches[6].str();
            regex var_regex(R"(([VI])\(([\w\d]+)\))");
            auto vars_begin = sregex_iterator(variables.begin(), variables.end(), var_regex);
            for (auto it = vars_begin; it != std::sregex_iterator(); ++it) {
                names_params.emplace_back((*it)[1].str(), (*it)[2].str());
            }
            //Controller::analyse
        }
    } else if (regex_match(line, matches, Cli_regexes::SHOW_SCHEMATICS)) {
        fileMenu();
    } else if (regex_match(line, matches, Cli_regexes::TRAN_ANALYSIS)) {
        double step = parseNumber(matches[1].str());
        double stop = parseNumber(matches[2].str());
        double start = 0, maxStep = 0;
        if (matches[4].matched) {
            start = parseNumber(matches[3].str());
        }
        if (matches[5].matched) {
            maxStep = parseNumber(matches[4].str());
        }

        //Controller::analyse
    } else if (regex_match(line, matches, Cli_regexes::DC_ANALYSIS)) {
        string SourceName = matches[1].str();
        double start = parseNumber(matches[2].str());
        double end = parseNumber(matches[3].str());
        double increment = parseNumber(matches[4].str());

        //Controller::analyse
    } else if (regex_match(line, matches, Cli_regexes::EXIT_CMD)) {
        exit(0);
    } else if (!line.empty())
        throw ParsingException(0);
}

double CLI::parseNumber(string n) {
    int exp;
    switch (n.back()) {
        case 'n':
            exp = -9;
            n.pop_back();
            break;
        case 'u':
            exp = -6;
            n.pop_back();
            break;
        case 'm':
            exp = -3;
            n.pop_back();
            break;
        case 'k':
            exp = 3;
            n.pop_back();
            break;
        case 'g':
            n.pop_back();
            n.pop_back();
        case 'M':
            exp = 6;
            n.pop_back();
            break;
        default:
            exp = 0;
    }
    return (stod(n) * pow(10, exp));
}


void CLI::fileMenu() {
    openFile(showFileMenu());
    string command;
    smatch matches;
    while (getline(cin, command)) {
        if (regex_match(command, matches, Cli_regexes::NEW_FILE)) {
        } else if (regex_match(command, matches, Cli_regexes::CHOOSE_SCHEMATIC)) {
        } else if (regex_match(command, matches, Cli_regexes::RETURN_CMD)) {
            return;
        }
    }
}

int CLI::showFileMenu() {
    cout << "-choose existing schematic:" << endl;
    for (int i = 0; i < files.size(); i++) {
        cout << i + 1 << '-' << ' ' << files.at(i).filename().generic_string() << endl;
    }
    string i;
    cin >> i;
    try {
        int n=stoi(i);
        if (n<=0||n>files.size())
            throw FileExp();
        return n - 1;
    }
    catch (...) {
        cout << "-Error : Inappropriate input"<<endl;
    }
}

void CLI::openFile(int n) {
    try {
        fstream file(files.at(n).c_str());
        if (!file.is_open()) {
            throw FileExp();
        }
        cout << files.at(n).filename().generic_string() << ": " << endl;
        while (file.good()) {
            string line;
            getline(file, line);
            cout << line << endl;
            if (line == ".end")
                return;
            string pr;
            if (line[0]!='.')
                pr ="add ";
            pr+= line ;
            if (line[0] != '*')
                prompt( pr);
        }
    } catch (FileExp &e) {
        cout << e.what() << endl;
    }
}

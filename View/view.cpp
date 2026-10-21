//
// Created by Arman on 5/27/2025.
//

#include "view.h"
#include "../Model/CLI_regexes.h"
#include "../Controller/controller.h"

CLI::CLI(Controller* controller):controller(controller) {
    fstream filesList("../Model/filesList.txt",ios::ate|ios::in|ios::out);
    int n=1;
    set<filesystem::path> ffiles;
    filesystem::create_directories("..\\files\\autosave\\"); // if it doesn't exist in the first place
    for (auto d: filesystem::directory_iterator("..\\files\\autosave\\")) {
     ffiles.emplace(d.path().stem());

    }
    n=ffiles.size()+1;
    string path="../files/autosave/"+to_string(n)+"_autosave.txt";
    fout.open(path.c_str());
    filesList<<path<<endl;
    filesList.seekg(0);
    string fileName;
    if (filesList.bad())
        throw FileExp();
    do  {
        getline(filesList,fileName);
        if (fileName.length()>0)
            files.push_back(fileName);
    }while(filesList.good());
    cout << "<****************--SPICE--****************>" << endl;
    cout << ">>";
    filesList.close();
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
        fout << name << ' ' << node1 << ' ' << node2 << ' ' << value <<endl;
        controller->addElement("resistor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::RESISTOR_DELETE)) {
        if (matches[1].str()[0] != 'R')
            throw ParsingException(2);
        controller->deleteElement(matches[1],"resistor");
    } else if (regex_match(line, matches, Cli_regexes::CAPACITOR_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'C')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        if (value <= 0)
            throw ParsingException(1, "Capacitance");
        fout << name << ' ' << node1 << ' ' << node2 << ' ' << value << endl;
        controller->addElement("capacitor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::CAPACITOR_DELETE)) {
        if (matches[1].str()[0] != 'C')
            throw ParsingException(2);
        controller->deleteElement(matches[1],"capacitor");
    } else if (regex_match(line, matches, Cli_regexes::INDUCTOR_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'L')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        if (value <= 0)
            throw ParsingException(1, "Inductance");
        fout << name << ' ' << node1 << ' ' << node2 << ' ' << value << endl;
        controller->addElement("inductor",name,node1,node2,value);
    } else if (regex_match(line, matches, Cli_regexes::INDUCTOR_DELETE)) {
        if (matches[1].str()[0] != 'L')
            throw ParsingException(2);
        controller->deleteElement(matches[1],"inductor");
    } else if (regex_match(line, matches, Cli_regexes::DIODE_ADD)) {
        string name = matches[1].str();
        if (name[0] != 'D')
            throw ParsingException(2, name);
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string model = matches[4].str();
        fout<< name << ' ' << node1 << ' ' << node2 << ' ' << model << endl;
        controller->addElement("diode",name,node1,node2,0,model);
    } else if (regex_match(line, matches, Cli_regexes::DIODE_DELETE)) {
        if (matches[1].str()[0] != 'D'&&matches[1].str()[0] != 'Z')
            throw ParsingException(2);
        controller->deleteElement(matches[1],"diode");
    } else if (regex_match(line, matches, Cli_regexes::GROUND_ADD)) {
        if (matches[1].str() != "GND")
            throw ParsingException(2, matches[1].str());
        string node = matches[2].str();
        controller->addGnd(node);
        fout <<matches[1].str() << ' ' << node << endl;
    } else if (regex_match(line, matches, Cli_regexes::GROUND_DELETE)) {
        if (matches[1].str() != "GND")
            throw ParsingException(2, matches[1].str());
        string node = matches[2].str();
        controller->deleteGnd(node);
    } else if (regex_match(line, matches, Cli_regexes::VOLTAGE_SOURCE_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        fout<<name<<' '<<node1<<' '<<node2<<' '<<value<<endl;
        controller->addElement("voltage Source",name,node1,node2,value,name);
    } else if (regex_match(line, matches, Cli_regexes::CURRENT_SOURCE_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double value = parseNumber(matches[4].str());
        fout<<name<<' '<<node1<<' '<<node2<<' '<<value<<endl;
        controller->addElement("current Source",name,node1,node2,value,name);
    } else if (regex_match(line, matches, Cli_regexes::SIN_SOURCE_ADD)) {
        // cout << "vsin\n";
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        double vOffset = parseNumber(matches[4].str());
        double vAmp = parseNumber(matches[5].str());
        double freq = parseNumber(matches[6].str());
        fout<<name<<' '<<node1<<' '<<node2<<" SINE("<<vOffset<<' '<<vAmp<<' '<<freq<<')'<<endl;
        controller->addElement("sine voltage source",name,node1,node2,vAmp,"",true,vOffset,freq);
    }
    else   if (regex_match(line,matches,Cli_regexes::PULSE_SOURCE_ADD)) {

    }
    else if (regex_match(line, matches, Cli_regexes::VCCS_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string ctrlNode1 = matches[4].str();
        string ctrlNode2 = matches[5].str();
        double value = parseNumber(matches[6].str());
        controller->addElement("VCCS",name,node1,node2,value,"",false,0,0,ctrlNode1,ctrlNode2);
        fout<<name<<' '<<node1<<' '<<node2<<' '<<ctrlNode1<<' '<<ctrlNode2<<' '<<value<<endl;
    } else if (regex_match(line, matches, Cli_regexes::VCVS_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string ctrlNode1 = matches[4].str();
        string ctrlNode2 = matches[5].str();
        double value = parseNumber(matches[6].str());
        controller->addElement("VCVS",name,node1,node2,value,"",false,0,0,ctrlNode1,ctrlNode2);
        fout<<name<<' '<<node1<<' '<<node2<<' '<<ctrlNode1<<' '<<ctrlNode2<<' '<<value<<endl;
    } else if (regex_match(line, matches, Cli_regexes::CCCS_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string ctrlNode1 = matches[4].str();
        double value = parseNumber(matches[5].str());
        controller->addElement("CCCS",name,node1,node2,value,"",false,0,0,ctrlNode1);
        fout<<name<<' '<<node1<<' '<<node2<<' '<<ctrlNode1<<' '<<value<<endl;
    } else if (regex_match(line, matches, Cli_regexes::CCVS_ADD)) {
        string name = matches[1].str();
        string node1 = matches[2].str();
        string node2 = matches[3].str();
        string ctrlNode1 = matches[4].str();
        double value = parseNumber(matches[5].str());
        controller->addElement("CCCS",name,node1,node2,value,"",false,0,0,ctrlNode1);
        fout<<name<<' '<<node1<<' '<<node2<<' '<<ctrlNode1<<' '<<value<<endl;
    }
    else if (regex_match(line, matches, Cli_regexes::NODES_LIST)) {
        controller->listNodes();
    } else if (regex_match(line, matches, Cli_regexes::NODE_RENAME)) {
        if (matches[1].str() != "node" && !matches[2].str().empty() && !matches[3].str().empty())
            throw ParsingException(4);
        controller->renameNode(matches[2].str(),matches[3].str());
        fout<<matches[0].str()<<endl;
    } else if (regex_match(line, matches, Cli_regexes::ELEMENTS_LIST)) {
        if (matches[1].length() > 0) {
            controller->listElementsByType(matches[1].str());
        } else {
            controller->listElements();
        }
    } else if (regex_match(line, matches, Cli_regexes::PRINT_COMMAND)) {
        //costume syntax error command not implemented
        string analysis = matches[1].str();
        controller->checkGnd();
        if (analysis == "TRAN") {
            double step = parseNumber(matches[2].str());
            double stop = parseNumber(matches[3].str());
            double start = 0;
            if (matches[4].matched) start = parseNumber(matches[4].str());

            vector<pair<char, string>> probes;
            string variables = matches[6].str();
            regex var_regex(R"(([VI])\(([\w\d]+)\))");
            auto vars_begin = sregex_iterator(variables.begin(), variables.end(), var_regex);
            for (auto it = vars_begin; it != std::sregex_iterator(); ++it) {
                probes.emplace_back((*it)[1].str()[0], (*it)[2].str());
            }

            controller->runTRAN(step, stop, start, probes);
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
    }
    else if (regex_match(line, matches, Cli_regexes::NEW_FILE)) {
        filesystem::path path=matches[1].str();
        if (path.extension()==".txt") {
            files.push_back(path);
            ofstream fileslist("../Model/filesList.txt");
            fileslist <<path.generic_string()<<endl;
            fout.close();
            fout.open(files.back().c_str(), ios::out | ios::app);
            controller->restart();
        }
        else
            throw FileExp();
    }else if (!line.empty())
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
        if (regex_match(command, matches, Cli_regexes::CHOOSE_SCHEMATIC)) {
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
    return 0;
}

void CLI::openFile(int n) {
    try {
        if (n<0||n>files.size())
            return;
        ifstream file(files.at(n).c_str());
        if (!file.is_open()) {
            throw FileExp();
        }
        controller->restart();
        fout.close();
        cout << files.at(n).filename().generic_string() << ": " << endl;
        while (file.good()) {
            string line;
            getline(file, line);
            cout << line << endl;
            if (line == ".end")
                return;
            string pr;
            if (line[0]!='.' && line[0]!='*')
                pr ="add ";
            pr+= line ;
            if (line[0] != '*'&&!line.empty())
                prompt( pr);
        }
        fout.open(files.at(n).c_str(), ios::out | ios::app);

    } catch (FileExp &e) {
        cout << e.what() << endl;
    }
}

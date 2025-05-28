//
// Created by Arman on 5/27/2025.
//

#include "view.h"
#include "../Model/CLI_regexes.h"
CLI::CLI() {
    cout<<"<****************--SPICE--****************>"<<endl;
    cout<<">>";
}

void CLI::prompt(string line) {
    cout<<">>";
    smatch matches;
    if (regex_match(line,matches,Cli_regexes::RESISTOR_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::RESISTOR_DELETE)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::CAPACITOR_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::CAPACITOR_DELETE)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::INDUCTOR_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::INDUCTOR_DELETE)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::DIODE_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::DIODE_DELETE)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::GROUND_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::GROUND_DELETE)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::VOLTAGE_SOURCE_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::CURRENT_SOURCE_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::SIN_SOURCE_ADD)) {

    }
    // else   if (regex_match(line,matches,Cli_regexes::PULSE_SOURCE_ADD)) {
    //
    // }
    else   if (regex_match(line,matches,Cli_regexes::VCCS_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::VCVS_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::CCCS_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::CCVS_ADD)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::NODES_LIST)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::NODE_RENAME)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::ELEMENTS_LIST)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::PRINT_DC_I)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::PRINT_DC_V)) {

    }
    else   if (regex_match(line,matches,Cli_regexes::PRINT_TRAN_I)) {

    }
    else if (regex_match(line,matches,Cli_regexes::PRINT_TRAN_V)) {

    }
    else if (regex_match(line,matches,Cli_regexes::NEW_FILE)) {

    }
    else if (regex_match(line,matches,Cli_regexes::SHOW_SCHEMATICS)) {

    }
    else if (regex_match(line,matches,Cli_regexes::CHOOSE_SCHEMATIC)) {

    }
    else if (regex_match(line,matches,Cli_regexes::TRAN_ANALYSIS)) {

    }
    else if (regex_match(line,matches,Cli_regexes::DC_ANALYSIS)) {

    }
    else if (regex_match(line,matches,Cli_regexes::RETURN_CMD)) {

    }

}

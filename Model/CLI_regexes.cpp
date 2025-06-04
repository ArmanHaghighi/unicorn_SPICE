//
// Created by Arman on 5/28/2025.
//

#include "CLI_regexes.h"

// Initialize static regex members
// Common number pattern with scientific notation and engineering suffixes
// This maintains the same match groups as before
const std::string NUM_PATTERN = R"([\d\.]+(?:[eE][+-]?\d+)?(?:Meg|M|k|m|u|n)?)";
const std::string NUM_PATTERN_S = R"([\d\.]+(?:[eE][+-]?\d+)?(?:Meg|M|k|m|u|n)?s?)";

// Resistor commands
const std::regex Cli_regexes::RESISTOR_ADD(R"(^\s*add\s+(R[\w\d]+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                           std::regex::icase);
const std::regex Cli_regexes::RESISTOR_DELETE(R"(^\s*delete\s+(R[\w\d]+)\s*$)", std::regex::icase);

// Capacitor commands
const std::regex Cli_regexes::CAPACITOR_ADD(R"(^\s*add\s+(C[\w\d]+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                            std::regex::icase);
const std::regex Cli_regexes::CAPACITOR_DELETE(R"(^\s*delete\s+(C[\w\d]+)\s*$)", std::regex::icase);

// Inductor commands
const std::regex Cli_regexes::INDUCTOR_ADD(R"(^\s*add\s+(L[\w\d]+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                           std::regex::icase);
const std::regex Cli_regexes::INDUCTOR_DELETE(R"(^\s*delete\s+(L[\w\d]+)\s*$)", std::regex::icase);

// Diode commands
const std::regex Cli_regexes::DIODE_ADD(R"(^\s*add\s+(D[\w\d]+)\s+(\w+)\s+(\w+)\s+(\w+)\s*$)", std::regex::icase);
const std::regex Cli_regexes::DIODE_DELETE(R"(^\s*delete\s+(D[\w\d]+)\s*$)", std::regex::icase);

// Ground commands
const std::regex Cli_regexes::GROUND_ADD(R"(^\s*add\s+GND\s*(\w+)\s*$)", std::regex::icase);
const std::regex Cli_regexes::GROUND_DELETE(R"(^\s*delete\s+GND\s*(\w+)\s*$)", std::regex::icase);

// Source commands
const std::regex Cli_regexes::VOLTAGE_SOURCE_ADD(R"(^\s*add\s+(?:VoltageSource\s+)?(V[\w\d]+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                                 std::regex::icase);
const std::regex Cli_regexes::CURRENT_SOURCE_ADD(R"(^\s*add\s+(?:CurrentSource\s+)?(I[\w\d]+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                                 std::regex::icase);
const std::regex Cli_regexes::SIN_SOURCE_ADD(
    R"(^\s*add\s+(V[\w\d]+)\s+(\w+)\s+(\w+)\s+SINE?\(\s*()" + NUM_PATTERN + R"()\s+()" + NUM_PATTERN + R"()\s+()" + NUM_PATTERN + R"()\s*\)\s*$)", std::regex::icase);
const std::regex Cli_regexes::PULSE_SOURCE_ADD(
    R"(^\s*add\s+V\s*([\w\d]+)\s+(\w+)\s+(\w+)\s+PULSE\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)", std::regex::icase);

// Dependent source commands
const std::regex Cli_regexes::VCVS_ADD(R"(^\s*add\s+(E[\w\d]+)\s+(\w+)\s+(\w+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                       std::regex::icase);
const std::regex Cli_regexes::VCCS_ADD(R"(^\s*add\s+(G[\w\d]+)\s+(\w+)\s+(\w+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                       std::regex::icase);
const std::regex Cli_regexes::CCVS_ADD(R"(^\s*add\s+(H[\w\d]+)\s+(\w+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                       std::regex::icase);
const std::regex Cli_regexes::CCCS_ADD(R"(^\s*add\s+(F[\w\d]+)\s+(\w+)\s+(\w+)\s+(\w+)\s+()" + NUM_PATTERN + R"()\s*$)",
                                       std::regex::icase);

// Node operations
const std::regex Cli_regexes::NODES_LIST(R"(^\s*\.nodes\s*$)", std::regex::icase);
const std::regex Cli_regexes::NODE_RENAME(R"(^\s*\.rename\s+node\s+(\w+)\s+(\w+)\s*$)", std::regex::icase);
const std::regex Cli_regexes::ELEMENTS_LIST(R"(^\s*\.list(?:\s+(\w+))?\s*$)", std::regex::icase);

// Print commands
const std::regex Cli_regexes::PRINT_COMMAND(
    R"(^\s*\.print\s+(\w+)(?:\s+()" + NUM_PATTERN_S + R"())?(?:\s+()" + NUM_PATTERN_S + R"())?(?:\s+()" + NUM_PATTERN_S + R"())?(?:\s+()" + NUM_PATTERN_S + R"())?\s+((?:([VI])\(([\w\d]+)\)(?:\s+|$))+)s*$)",
    std::regex::icase);

// File operations
const std::regex Cli_regexes::NEW_FILE(R"(^\s*NewFile\s+(\S+)\s*$)", std::regex::icase);
const std::regex Cli_regexes::SHOW_SCHEMATICS(R"(^\s*\-show\s+existing\s+schematics\s*$)", std::regex::icase);
const std::regex Cli_regexes::CHOOSE_SCHEMATIC(R"(^\s*\-choose\s+existing\s+schematic:\s*(\d+)\s*$)", std::regex::icase);
const std::regex Cli_regexes::RETURN_CMD(R"(^\s*return\s*$)", std::regex::icase);

// Analysis commands
const std::regex Cli_regexes::TRAN_ANALYSIS(
    R"(^\s*\.?TRAN\s+()" + NUM_PATTERN_S + R"()\s+()" + NUM_PATTERN_S + R"()(?:\s+()" + NUM_PATTERN_S + R"())?(?:\s+()" + NUM_PATTERN_S + R"())?\s*$)",
    std::regex::icase);
const std::regex Cli_regexes::DC_ANALYSIS(R"(^\s*DC\s+(\w+)\s+()" + NUM_PATTERN + R"()\s+()" + NUM_PATTERN + R"()\s+()" + NUM_PATTERN + R"()\s*$)",
                                          std::regex::icase);
const std::regex Cli_regexes::EXIT_CMD(R"(^\s*exit\s*$)", std::regex::icase);

std::string Cli_regexes::trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
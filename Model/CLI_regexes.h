//
// Created by Arman on 5/28/2025.
//
#pragma once
#include <regex>
#ifndef CLI_REGEXES_H
#define CLI_REGEXES_H

class Cli_regexes {
    public:
    // Resistor commands
    // Command: add R<name> <node1> <node2> <value>
    static const std::regex RESISTOR_ADD;

    // Command: delete R<name>
    static const std::regex RESISTOR_DELETE;

    // Capacitor commands
    // Command: add C<name> <node1> <node2> <value>
    static const std::regex CAPACITOR_ADD;

    // Command: delete C<name>
    static const std::regex CAPACITOR_DELETE;

    // Inductor commands
    // Command: add L<name> <node1> <node2> <value>
    static const std::regex INDUCTOR_ADD;

    // Command: delete L<name>
    static const std::regex INDUCTOR_DELETE;

    // Diode commands
    // Command: add D<name> <node1> <node2> <model>
    static const std::regex DIODE_ADD;

    // Command: delete D<name>
    static const std::regex DIODE_DELETE;

    // Ground commands
    // Command: add GND <node>
    static const std::regex GROUND_ADD;

    // Command: delete GND <node>
    static const std::regex GROUND_DELETE;

    // Source commands
    // Command: add VoltageSource<Name> <Node1> <Node2> <Value>
    static const std::regex VOLTAGE_SOURCE_ADD;

    // Command: add CurrentSource<Name> <Node1> <Node2> <Value>
    static const std::regex CURRENT_SOURCE_ADD;

    // Command: add V<name> <node+> <node-> SIN(<Voffset> <Vamplitude> <Frequency>)
    static const std::regex SIN_SOURCE_ADD;

    // Command: add V<name> <node+> <node-> PULSE <type> <Value> (Bonus)
    static const std::regex PULSE_SOURCE_ADD;

    // Dependent source commands (Bonus)
    // Command: add E<Name> <Node1> <Node2> <CtrlNode1> <CtrlNode2> <Gain>
    static const std::regex VCVS_ADD;

    // Command: add G<Name> <Node+> <Node-> <Control+> <Control-> <Gain>
    static const std::regex VCCS_ADD;

    // Command: add H<Name> <Node+> <Node-> <vname> <gain>
    static const std::regex CCVS_ADD;

    // Command: add F<Name> <Node+> <Node-> <vname> <gain>
    static const std::regex CCCS_ADD;

    // Node operations
    // Command: .nodes
    static const std::regex NODES_LIST;

    // Command: .rename node <old_name> <new_name>
    static const std::regex NODE_RENAME;

    // Command: .list [component_type]
    static const std::regex ELEMENTS_LIST;

    // Print commands
    // Command: .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(<node>)
    // Command: .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] I(<component>)
    // Command: .print DC <SourceName> <StartValue> <EndValue> <Increment> V(<node>)
    // Command: .print DC <SourceName> <StartValue> <EndValue> <Increment> I(<component>)

    static const std::regex PRINT_COMMAND;

    // File operations
    // Command: NewFile <file_path>
    static const std::regex NEW_FILE;

    // Command: -show existing schematics
    static const std::regex SHOW_SCHEMATICS;

    // Command: -choose existing schematic: <number>
    static const std::regex CHOOSE_SCHEMATIC;

    // Command: return
    static const std::regex RETURN_CMD;

    // Analysis commands
    // Command: TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>]
    static const std::regex TRAN_ANALYSIS;

    // Command: DC <SourceName> <StartValue> <EndValue> <Increment>
    static const std::regex DC_ANALYSIS;

    static const std::regex EXIT_CMD;

    // Utility function
    static std::string trim(const std::string& str);
};

#endif //CLI_REGEXES_H

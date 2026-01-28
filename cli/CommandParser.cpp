#include "CommandParser.h"
#include <sstream>

Command CommandParser::parse(const std::string& input) {
    std::istringstream iss(input);
    Command cmd;
    iss >> cmd.name;
    std::string arg;
    while (iss >> arg) {
        cmd.args.push_back(arg);
    }
    return cmd;
}

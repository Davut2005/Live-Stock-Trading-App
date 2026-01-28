#include "CLI.h"
#include "CommandParser.h"
#include "CommandHandlers.h"
#include <iostream>

CLI::CLI(std::shared_ptr<Trader> trader,
         std::shared_ptr<MarketDataManager> market)
    : trader_(trader), market_(market) {}

void CLI::displayWelcome() {
    std::cout << "===================================\n";
    std::cout << " Welcome to Live Stock Trading CLI \n";
    std::cout << " Type 'help' to see available commands\n";
    std::cout << "===================================\n";
}

void CLI::displayHelp() {
    CommandHandlers::handleHelp();
}

void CLI::executeCommand(const std::string& cmdLine) {
    auto cmd = CommandParser::parse(cmdLine);

    if (cmd.name == "help") {
        displayHelp();
    } else if (cmd.name == "buy") {
        CommandHandlers::handleBuy(cmd, trader_, market_);
    } else if (cmd.name == "sell") {
        CommandHandlers::handleSell(cmd, trader_, market_);
    } else if (cmd.name == "portfolio") {
        CommandHandlers::handlePortfolio(trader_->getPortfolio());
    } else if (cmd.name == "history") {
        CommandHandlers::handleHistory(cmd, market_);
    } else if (cmd.name == "price") {
        CommandHandlers::handlePrice(cmd, market_);
    } else if (cmd.name == "stats") {
        CommandHandlers::handleStats(cmd, market_);
    } else if (cmd.name == "assets") {
        CommandHandlers::handleAssets(trader_);
    } else if (cmd.name == "exit") {
        std::exit(0);
    } else {
        std::cout << "Unknown command! Type 'help' for commands.\n";
    }
}

void CLI::run() {
    displayWelcome();
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (!line.empty()) executeCommand(line);
    }
}

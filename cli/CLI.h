#pragma once
#include <string>
#include <memory>
#include "Portfolio.h"
#include "Trader.h"
#include "MarketDataManager.h"

class CLI {
public:
    CLI(std::shared_ptr<Trader> trader,
        std::shared_ptr<MarketDataManager> market);

    void run();  // main loop

private:
    std::shared_ptr<Trader> trader_;

    std::shared_ptr<MarketDataManager> market_;

    void displayWelcome();
    void displayHelp();
    void executeCommand(const std::string& cmdLine);
};

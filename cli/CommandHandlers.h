#pragma once
#include "CommandParser.h"
#include "Trader.h"
#include "Portfolio.h"
#include "MarketDataManager.h"

class CommandHandlers {
public:
    static void handleBuy(const Command& cmd,
                          std::shared_ptr<Trader> trader,
                          std::shared_ptr<MarketDataManager> market);

    static void handleSell(const Command& cmd,
                           std::shared_ptr<Trader> trader,
                           std::shared_ptr<MarketDataManager> market);

    static void handlePortfolio(const Portfolio& portfolio);

    static void handleHistory(const Command& cmd,
                              std::shared_ptr<MarketDataManager> market);

    static void handlePrice(const Command& cmd,
                            std::shared_ptr<MarketDataManager> market);

    static void handleStats(const Command& cmd,
                            std::shared_ptr<MarketDataManager> market);

    static void handleAssets(std::shared_ptr<Trader> trader);
    
    static void handleHelp();
};

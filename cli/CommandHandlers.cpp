#include "CommandHandlers.h"
#include "StockFactory.h"
#include <iostream>

void CommandHandlers::handleBuy(const Command& cmd,
                                std::shared_ptr<Trader> trader,
                                std::shared_ptr<MarketDataManager> market) {
    if (cmd.args.size() < 2) {
        std::cout << "Usage: buy <symbol> <quantity>\n";
        return;
    }
    std::string symbol = cmd.args[0];
    int qty = std::stoi(cmd.args[1]);
    double price = market->getLatestPrice(symbol);
    
    // Default to tech stock for CLI purchases for now
    auto stock = StockFactory::create("tech", symbol, price, 0.0);
    trader->buyStock(std::move(stock), qty);
    
    std::cout << "Bought " << qty << " shares of " << symbol << " at " << price << "\n";
}

void CommandHandlers::handleSell(const Command& cmd,
                                 std::shared_ptr<Trader> trader,
                                 std::shared_ptr<MarketDataManager> market) {
    if (cmd.args.size() < 2) {
        std::cout << "Usage: sell <symbol> <quantity>\n";
        return;
    }
    std::string symbol = cmd.args[0];
    int qty = std::stoi(cmd.args[1]);
    double price = market->getLatestPrice(symbol);
    trader->sellStock(symbol, qty, price);
    std::cout << "Sold " << qty << " shares of " << symbol << " at " << price << "\n";
}

void CommandHandlers::handlePortfolio(const Portfolio& portfolio) {
    std::cout << "Portfolio Contents:\n";
    for (const auto& stock : portfolio.getStocks()) {
        std::cout << stock->getName() << " x" << stock->getQuantity()
                  << " at $" << stock->getPrice() << "\n";
    }
}

void CommandHandlers::handleHistory(const Command& cmd,
                                    std::shared_ptr<MarketDataManager> market) {
    if (cmd.args.empty()) {
        std::cout << "Usage: history <symbol>\n";
        return;
    }
    auto prices = market->getPriceHistory(cmd.args[0]);
    std::cout << "Price history for " << cmd.args[0] << ":\n";
    for (double p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
}

void CommandHandlers::handlePrice(const Command& cmd,
                                  std::shared_ptr<MarketDataManager> market) {
    if (cmd.args.empty()) {
        std::cout << "Usage: price <symbol>\n";
        return;
    }
    double price = market->getLatestPrice(cmd.args[0]);
    std::cout << "Current price of " << cmd.args[0] << ": $" << price << "\n";
}

void CommandHandlers::handleStats(const Command& cmd,
                                  std::shared_ptr<MarketDataManager> market) {
    if (cmd.args.empty()) {
        std::cout << "Usage: stats <symbol>\n";
        return;
    }
    std::string symbol = cmd.args[0];
    auto history = market->getPriceHistory(symbol);
    
    if (history.empty()) {
        std::cout << "No data for " << symbol << "\n";
        return;
    }

    double minP = history[0];
    double maxP = history[0];
    double sumP = 0;

    for (double p : history) {
        if (p < minP) minP = p;
        if (p > maxP) maxP = p;
        sumP += p;
    }
    double avgP = sumP / history.size();

    std::cout << "Statistics for " << symbol << ":\n";
    std::cout << "  Min Price: " << minP << "\n";
    std::cout << "  Max Price: " << maxP << "\n";
    std::cout << "  Avg Price: " << avgP << "\n";
}

void CommandHandlers::handleAssets(std::shared_ptr<Trader> trader) {
    double balance = trader->getBalance();
    double stockValue = trader->getPortfolio().totalValue();
    double netWorth = balance + stockValue;

    std::cout << "--- Asset Summary ---\n";
    std::cout << "Cash Balance: $" << balance << "\n";
    std::cout << "Stock Holdings: $" << stockValue << "\n";
    std::cout << "Total Net Worth: $" << netWorth << "\n";
}

void CommandHandlers::handleHelp() {
    std::cout << "Available commands:\n";
    std::cout << "  buy <symbol> <quantity>   - Buy stock\n";
    std::cout << "  sell <symbol> <quantity>  - Sell stock\n";
    std::cout << "  portfolio                 - View holdings\n";
    std::cout << "  assets                    - View total net worth\n";
    std::cout << "  history <symbol>          - View price history\n";
    std::cout << "  price <symbol>            - View current price\n";
    std::cout << "  stats <symbol>            - View stock statistics\n";
    std::cout << "  exit                      - Exit application\n";
}

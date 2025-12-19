#include "../includes/Trader.h"
#include <vector>

std::vector<Trader> createTraders() {
    std::vector<Trader> traders;
    traders.emplace_back("Alice", 50000.0);
    traders.emplace_back("Bob", 30000.0);
    traders.emplace_back("Charlie", 100000.0);
    traders.emplace_back("Diana", 75000.0);
    return traders;
}

#include "CLI.h"
#include "Trader.h"
#include "Portfolio.h"
#include "MarketDataManager.h"
#include <memory>

int main() {
    auto trader = std::make_shared<Trader>("CLI User", 10000.0);
    auto market = std::make_shared<MarketDataManager>();

    market->updatePrice("GOOG", 2800.0);
    market->updatePrice("TSLA", 700.0);

    CLI cli(trader, market);
    cli.run();

    return 0;
}

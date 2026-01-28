#pragma once
#include "../../libs/crow.h"
#include "Trader.h"
#include <memory>

class PortfolioRouter {
public:
    static void registerRoutes(crow::SimpleApp& app, std::shared_ptr<Trader> trader);
};

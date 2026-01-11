#pragma once
#include <memory>
#include <string>
#include "Stock.h"

class StockFactory {
public:
    static std::unique_ptr<Stock> create(
        const std::string& type,
        const std::string& name,
        double price,
        int quantity
    );
};

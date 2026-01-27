#pragma once
#include <string>
#include <vector>
#include <map>

class HistoricalData {
public:
    struct PricePoint {
        std::string date;
        double open;
        double high;
        double low;
        double close;
        long volume;
    };

    static const std::vector<PricePoint>& get(const std::string& symbol);
    static bool hasData(const std::string& symbol);

private:
   static std::map<std::string, std::vector<PricePoint>> data;
   static void initialize();
   static bool initialized;
};

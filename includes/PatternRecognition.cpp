#include "PatternRecognition.h"
#include <cmath>
#include <algorithm>

std::vector<PatternRecognition::PatternResult> PatternRecognition::scan(const std::vector<HistoricalData::PricePoint>& data) {
    std::vector<PatternResult> results;
    if (data.size() < 3) return results;

    for (size_t i = 2; i < data.size(); ++i) {
        const auto& prev2 = data[i-2];
        const auto& prev = data[i-1];
        const auto& curr = data[i];

        if (isDoji(curr)) {
            results.push_back({curr.date, DOJI, 0.6});
        }
        if (isHammer(curr)) {
            results.push_back({curr.date, HAMMER, 0.7});
        }
        if (isShootingStar(curr)) {
            results.push_back({curr.date, SHOOTING_STAR, 0.7});
        }
        if (isEngulfingBullish(prev, curr)) {
            results.push_back({curr.date, ENGULFING_BULLISH, 0.8});
        }
        if (isEngulfingBearish(prev, curr)) {
            results.push_back({curr.date, ENGULFING_BEARISH, 0.8});
        }
        if (isMarubozuWhite(curr)) {
            results.push_back({curr.date, MARUBOZU_WHITE, 0.65});
        }
        if (isMarubozuBlack(curr)) {
            results.push_back({curr.date, MARUBOZU_BLACK, 0.65});
        }
        if (isSpinningTop(curr)) {
            results.push_back({curr.date, SPINNING_TOP, 0.5});
        }

        // Morning Star (3-candle pattern)
        // 1. Long bearish
        // 2. Small gap down
        // 3. Long bullish
        bool c1_bear = prev2.close < prev2.open;
        bool c2_small = std::abs(prev.close - prev.open) < (prev.high - prev.low) * 0.3;
        bool c3_bull = curr.close > curr.open;
        if (c1_bear && c2_small && c3_bull && curr.close > (prev2.open + prev2.close)/2) {
             results.push_back({curr.date, MORNING_STAR, 0.85});
        }

        // Three White Soldiers
        if (prev2.close > prev2.open && prev.close > prev.open && curr.close > curr.open &&
            prev.close > prev2.close && curr.close > prev.close &&
            prev.open > prev2.open && prev.open < prev2.close &&
            curr.open > prev.open && curr.open < prev.close) {
             results.push_back({curr.date, THREE_WHITE_SOLDIERS, 0.9});
        }
    }
    return results;
}

bool PatternRecognition::isDoji(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    return range > 0 && body <= range * 0.1;
}

bool PatternRecognition::isHammer(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    double lowerShadow = std::min(p.close, p.open) - p.low;
    double upperShadow = p.high - std::max(p.close, p.open);
    
    return range > 0 && 
           lowerShadow >= body * 2.0 && 
           upperShadow <= body * 0.1; 
}

bool PatternRecognition::isShootingStar(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    double lowerShadow = std::min(p.close, p.open) - p.low;
    double upperShadow = p.high - std::max(p.close, p.open);
    
    return range > 0 && 
           upperShadow >= body * 2.0 && 
           lowerShadow <= body * 0.1;
}

bool PatternRecognition::isEngulfingBullish(const HistoricalData::PricePoint& prev, const HistoricalData::PricePoint& curr) {
    bool prevBearish = prev.close < prev.open;
    bool currBullish = curr.close > curr.open;
    return prevBearish && currBullish && 
           curr.open < prev.close && // Opens lower than prev close (gap down)
           curr.close > prev.open;   // Closes higher than prev open
}

bool PatternRecognition::isEngulfingBearish(const HistoricalData::PricePoint& prev, const HistoricalData::PricePoint& curr) {
    bool prevBullish = prev.close > prev.open;
    bool currBearish = curr.close < curr.open;
    return prevBullish && currBearish && 
           curr.open > prev.close && // Opens higher (gap up)
           curr.close < prev.open;   // Closes lower
}

bool PatternRecognition::isMarubozuWhite(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    return range > 0 && body > range * 0.9; // Almost all body, bullish
}

bool PatternRecognition::isMarubozuBlack(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    return range > 0 && body > range * 0.9 && p.close < p.open; // Bearish
}

bool PatternRecognition::isSpinningTop(const HistoricalData::PricePoint& p) {
    double body = std::abs(p.close - p.open);
    double range = p.high - p.low;
    double lowerShadow = std::min(p.close, p.open) - p.low;
    double upperShadow = p.high - std::max(p.close, p.open);

    // Small body centered in large range
    return range > 0 && 
           body < range * 0.3 && 
           lowerShadow > body && 
           upperShadow > body;
}

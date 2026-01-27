#pragma once
#include <vector>
#include <string>
#include "../includes/HistoricalData.h"

class PatternRecognition {
public:
    enum PatternType {
        DOJI,
        HAMMER,
        SHOOTING_STAR,
        ENGULFING_BULLISH,
        ENGULFING_BEARISH,
        MORNING_STAR,
        EVENING_STAR,
        MARUBOZU_WHITE,
        MARUBOZU_BLACK,
        SPINNING_TOP,
        THREE_WHITE_SOLDIERS,
        THREE_BLACK_CROWS,
        PIERCING_LINE,
        DARK_CLOUD_COVER,
        HARAMI_BULLISH,
        HARAMI_BEARISH,
        NONE
    };

    struct PatternResult {
        std::string date;
        PatternType type;
        double reliability; // 0.0 to 1.0
    };

    static std::vector<PatternResult> scan(const std::vector<HistoricalData::PricePoint>& data);

private:
    static bool isDoji(const HistoricalData::PricePoint& p);
    static bool isHammer(const HistoricalData::PricePoint& p);
    static bool isShootingStar(const HistoricalData::PricePoint& p);
    static bool isEngulfingBullish(const HistoricalData::PricePoint& prev, const HistoricalData::PricePoint& curr);
    static bool isEngulfingBearish(const HistoricalData::PricePoint& prev, const HistoricalData::PricePoint& curr);
    static bool isMarubozuWhite(const HistoricalData::PricePoint& p);
    static bool isMarubozuBlack(const HistoricalData::PricePoint& p);
    static bool isSpinningTop(const HistoricalData::PricePoint& p);
};

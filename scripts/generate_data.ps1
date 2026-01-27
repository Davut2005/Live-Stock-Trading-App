$file = "c:\Users\Dayanch Yangiyev\Desktop\davut\Live-Stock-Trading-App\data\HistoricalData.cpp"

$content = @"
#include "../includes/HistoricalData.h"

std::map<std::string, std::vector<HistoricalData::PricePoint>> HistoricalData::data;
bool HistoricalData::initialized = false;

const std::vector<HistoricalData::PricePoint>& HistoricalData::get(const std::string& symbol) {
    if (!initialized) {
        initialize();
    }
    static const std::vector<PricePoint> empty;
    auto it = data.find(symbol);
    return (it != data.end()) ? it->second : empty;
}

bool HistoricalData::hasData(const std::string& symbol) {
    if (!initialized) initialize();
    return data.find(symbol) != data.end();
}

void HistoricalData::initialize() {
    if (initialized) return;

    // AAPL Data
    std::vector<PricePoint> aapl;
"@

# Generate 2000 lines for AAPL
python -c "import random; p=150.0; 
for i in range(2000): 
    change = random.uniform(-2, 2); 
    p+=change; 
    print(f'    aapl.push_back({{\`"2023-01-01\`", {p:.2f}, {p+2:.2f}, {p-2:.2f}, {p+change:.2f}, 50000000}});')" | Out-String -Stream >> $file

$content += @"
    data["AAPL"] = aapl;

    // BTC Data
    std::vector<PricePoint> btc;
"@

# Generate 2000 lines for BTC
python -c "import random; p=30000.0; 
for i in range(2000): 
    change = random.uniform(-100, 100); 
    p+=change; 
    print(f'    btc.push_back({{\`"2023-01-01\`", {p:.2f}, {p+200:.2f}, {p-200:.2f}, {p+change:.2f}, 1000000}});')" | Out-String -Stream >> $file

$content += @"
    data["BTC"] = btc;

    // TSLA Data
    std::vector<PricePoint> tsla;
"@

# Generate 2000 lines for TSLA
python -c "import random; p=200.0; 
for i in range(2000): 
    change = random.uniform(-5, 5); 
    p+=change; 
    print(f'    tsla.push_back({{\`"2023-01-01\`", {p:.2f}, {p+10:.2f}, {p-10:.2f}, {p+change:.2f}, 25000000}});')" | Out-String -Stream >> $file

$content += @"
    data["TSLA"] = tsla;

    initialized = true;
}
"@

# Write the C++ header and footer manually, but inject the python output
$head = @"
#include "../includes/HistoricalData.h"

std::map<std::string, std::vector<HistoricalData::PricePoint>> HistoricalData::data;
bool HistoricalData::initialized = false;

const std::vector<HistoricalData::PricePoint>& HistoricalData::get(const std::string& symbol) {
    if (!initialized) {
        initialize();
    }
    static const std::vector<PricePoint> empty;
    auto it = data.find(symbol);
    return (it != data.end()) ? it->second : empty;
}

bool HistoricalData::hasData(const std::string& symbol) {
    if (!initialized) initialize();
    return data.find(symbol) != data.end();
}

void HistoricalData::initialize() {
    if (initialized) return;

    // AAPL Data
    std::vector<PricePoint> aapl;
"@

Set-Content -Path $file -Value $head

# Append AAPL data
python -c "import random; p=150.0; 
for i in range(2000): 
    change = random.uniform(-2, 2); 
    p+=change; 
    print(f'    aapl.push_back({{\`"2023-01-01\`", {p:.2f}, {p+2:.2f}, {p-2:.2f}, {p+change:.2f}, 50000000}});')" | Out-File -FilePath $file -Append -Encoding utf8

Add-Content -Path $file -Value "    data[`"AAPL`"] = aapl;"
Add-Content -Path $file -Value "    std::vector<PricePoint> btc;"

# Append BTC data
python -c "import random; p=30000.0; 
for i in range(2000): 
    change = random.uniform(-100, 100); 
    p+=change; 
    print(f'    btc.push_back({{\`"2023-01-01\`", {p:.2f}, {p+200:.2f}, {p-200:.2f}, {p+change:.2f}, 1000000}});')" | Out-File -FilePath $file -Append -Encoding utf8

Add-Content -Path $file -Value "    data[`"BTC`"] = btc;"
Add-Content -Path $file -Value "    std::vector<PricePoint> tsla;"

# Append TSLA data
python -c "import random; p=200.0; 
for i in range(2000): 
    change = random.uniform(-5, 5); 
    p+=change; 
    print(f'    tsla.push_back({{\`"2023-01-01\`", {p:.2f}, {p+10:.2f}, {p-10:.2f}, {p+change:.2f}, 25000000}});')" | Out-File -FilePath $file -Append -Encoding utf8

Add-Content -Path $file -Value "    data[`"TSLA`"] = tsla;"
Add-Content -Path $file -Value "    initialized = true;"
Add-Content -Path $file -Value "}"

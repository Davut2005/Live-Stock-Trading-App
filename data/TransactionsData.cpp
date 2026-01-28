#include <vector>
#include <string>
#include <ctime>

struct TransactionDataStructure {
    std::string symbol;
    std::string type; // "BUY" or "SELL"
    int quantity;
    double price;
    std::string timestamp;
};

std::vector<TransactionDataStructure> createMockTransactions() {
    std::vector<TransactionDataStructure> transactions;
    transactions.push_back({"AAPL", "BUY", 10, 150.0, "2023-01-01 10:00:00"});
    transactions.push_back({"GOOG", "BUY", 5, 2800.0, "2023-01-02 11:30:00"});
    transactions.push_back({"TSLA", "SELL", 2, 700.0, "2023-01-03 09:15:00"});
    transactions.push_back({"MSFT", "BUY", 15, 250.0, "2023-01-04 14:00:00"});
    transactions.push_back({"AMZN", "BUY", 20, 140.0, "2023-01-05 10:45:00"});
    transactions.push_back({"AAPL", "SELL", 5, 155.0, "2023-01-06 13:20:00"});
    transactions.push_back({"NVDA", "BUY", 8, 450.0, "2023-01-07 11:00:00"});
    transactions.push_back({"JNJ", "BUY", 12, 160.0, "2023-01-08 09:30:00"});
    transactions.push_back({"PFE", "BUY", 100, 35.0, "2023-01-09 15:10:00"});
    transactions.push_back({"XOM", "BUY", 30, 110.0, "2023-01-10 10:00:00"});
    transactions.push_back({"BTC", "BUY", 1, 30000.0, "2023-01-11 12:00:00"});
    transactions.push_back({"ETH", "BUY", 5, 1900.0, "2023-01-12 09:00:00"});
    transactions.push_back({"GOOG", "SELL", 2, 2850.0, "2023-01-13 14:30:00"});
    transactions.push_back({"TSLA", "BUY", 10, 680.0, "2023-01-14 10:15:00"});
    transactions.push_back({"AMD", "BUY", 50, 110.0, "2023-01-15 11:45:00"});
    transactions.push_back({"INTC", "SELL", 20, 35.0, "2023-01-16 13:00:00"});
    transactions.push_back({"CVX", "BUY", 10, 160.0, "2023-01-17 09:45:00"});
    transactions.push_back({"SHEL", "BUY", 40, 60.0, "2023-01-18 10:30:00"});
    transactions.push_back({"UNH", "BUY", 3, 480.0, "2023-01-19 14:15:00"});
    transactions.push_back({"LLY", "BUY", 4, 450.0, "2023-01-20 11:10:00"});
    transactions.push_back({"MSFT", "SELL", 5, 260.0, "2023-01-21 15:00:00"});
    return transactions;
}

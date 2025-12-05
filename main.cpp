#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for std::fixed and std::setprecision

// ==============================
//          CLASS: Stock
// ==============================
class Stock {
private:
    std::string name;
    double price;
    int quantity;

public:
    // --- Constructors ---
    Stock() : name("Unknown"), price(0.0), quantity(0) {
        std::cout << "Stock default constructed.\n";
    }

    explicit Stock(const std::string& n, double p = 0.0, int q = 0)
        : name(n), price(p), quantity(q) {
        std::cout << "Stock initialized with values.\n";
    }

    Stock(const Stock& other) {
        name = other.name;
        price = other.price;
        quantity = other.quantity;
        std::cout << "Stock copy constructed.\n";
    }

    Stock& operator=(const Stock& other) {
        if (this != &other) {
            name = other.name;
            price = other.price;
            quantity = other.quantity;
        }
        std::cout << "Stock copy assigned using *this.\n";
        return *this;
    }

    Stock(Stock&& other) noexcept {
        name = std::move(other.name);
        price = other.price;
        quantity = other.quantity;
        std::cout << "Stock move constructed.\n";
    }

    Stock& operator=(Stock&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            price = other.price;
            quantity = other.quantity;
        }
        std::cout << "Stock move assigned.\n";
        return *this;
    }

    ~Stock() {
        std::cout << "Stock " << name << " destroyed.\n";
    }

    // --- Getters and Setters ---
    const std::string& getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setPrice(double p) {
        if (p > 0)
            price = p;
    }

    void setQuantity(int q) {
        if (q >= 0)
            quantity = q;
    }

    // --- Public Member Functions ---
    void updatePrice(double percentChange) {
        price *= (1 + percentChange / 100);
    }

    double totalValue() const {
        return price * quantity;
    }

    void addQuantity(int q) {
        if (q > 0)
            quantity += q;
    }

    void removeQuantity(int q) {
        if (q > 0 && q <= quantity)
            quantity -= q;
    }

    bool isExpensive(double threshold) const {
        return price > threshold;
    }

    void display() const {
        std::cout << "Stock: " << name
                  << " | Price: " << price
                  << " | Quantity: " << quantity
                  << " | Value: " << totalValue() << "\n";
    }

    // --- Operator Overloads ---
    friend std::ostream& operator<<(std::ostream& os, const Stock& s) {
        os << "Stock(" << s.name << ", price=" << s.price
           << ", qty=" << s.quantity << ")";
        return os;
    }

    bool operator==(const Stock& other) const {
        return name == other.name;
    }

    bool operator<(const Stock& other) const {
        return price < other.price;
    }
};


// ==============================
//         CLASS: Portfolio
// ==============================
class Portfolio {
private:
    std::vector<Stock> stocks;

public:
    Portfolio() = default;
    Portfolio(const Portfolio&) = default;
    Portfolio& operator=(const Portfolio&) = default;
    ~Portfolio() = default;

    Portfolio(Portfolio&&) = delete;
    Portfolio& operator=(Portfolio&&) = delete;

    // --- Add, Remove, Find ---
    void addStock(const Stock& s) {
        stocks.push_back(s);
        std::cout << s.getName() << " added to portfolio.\n";
    }

    void removeStock(const std::string& stockName) {
        for (auto it = stocks.begin(); it != stocks.end(); ++it) {
            if (it->getName() == stockName) {
                std::cout << "Removing stock: " << it->getName() << "\n";
                stocks.erase(it);
                return;
            }
        }
        std::cout << "Stock " << stockName << " not found in portfolio.\n";
    }

    Stock* findStock(const std::string& stockName) {
        for (auto& s : stocks) {
            if (s.getName() == stockName)
                return &s;
        }
        return nullptr;
    }

    // --- Calculations ---
    double totalValue() const {
        double sum = 0;
        for (const auto& s : stocks)
            sum += s.totalValue();
        return sum;
    }

    int totalQuantity() const {
        int sum = 0;
        for (const auto& s : stocks)
            sum += s.getQuantity();
        return sum;
    }

    // --- Display ---
    void showAll() const {
        std::cout << "\nPortfolio contents:\n";
        for (const auto& s : stocks)
            std::cout << "  " << s << "\n";
        std::cout << "---------------------------\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Portfolio& p) {
        os << "Portfolio(total stocks: " << p.stocks.size()
           << ", total value: " << std::fixed << std::setprecision(2)
           << p.totalValue() << ")";
        return os;
    }
};


// ==============================
//           CLASS: Trader
// ==============================
class Trader {
private:
    std::string name;
    double balance;
    Portfolio portfolio;

public:
    Trader() : name("Anonymous"), balance(0.0) {
        std::cout << "Trader default constructed.\n";
    }

    Trader(const std::string& n, double b = 1000.0)
        : name(n), balance(b) {
        std::cout << "Trader " << name << " initialized with balance $" << balance << ".\n";
    }

    // Copy constructor
    Trader(const Trader& other)
        : name(other.name), balance(other.balance), portfolio(other.portfolio) {
        std::cout << "Trader copy constructed.\n";
    }

    Trader& operator=(const Trader& other) {
        if (this != &other) {
            name = other.name;
            balance = other.balance;
            portfolio = other.portfolio;
        }
        std::cout << "Trader copy assigned.\n";
        return *this;
    }

    ~Trader() {
        std::cout << "Trader " << name << " destroyed.\n";
    }

    // --- Public Functions ---
    void buyStock(const Stock& stock, int quantity) {
        double totalCost = stock.getPrice() * quantity;
        if (balance >= totalCost) {
            balance -= totalCost;
            Stock s(stock.getName(), stock.getPrice(), quantity);
            portfolio.addStock(s);
            std::cout << name << " bought " << quantity << " shares of " << stock.getName() << ".\n";
        } else {
            std::cout << "Not enough balance to buy " << stock.getName() << ".\n";
        }
    }

    void sellStock(const std::string& stockName, int quantity, double sellPrice) {
        Stock* s = portfolio.findStock(stockName);
        if (s && s->getQuantity() >= quantity) {
            double revenue = quantity * sellPrice;
            s->removeQuantity(quantity);
            balance += revenue;
            std::cout << name << " sold " << quantity << " shares of " << stockName
                      << " for $" << revenue << ".\n";
            if (s->getQuantity() == 0)
                portfolio.removeStock(stockName);
        } else {
            std::cout << "Cannot sell " << quantity << " shares of " << stockName << ".\n";
        }
    }

    void displayPortfolio() const {
        std::cout << "\nTrader: " << name << "\nBalance: $" << balance << "\n";
        std::cout << portfolio << "\n";
    }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
    }
};


// ==============================
//             MAIN
// ==============================
int main() {
    std::cout << "--- Creating Stocks ---\n";
    Stock apple("AAPL", 180.5);
    Stock tesla("TSLA", 250.0);
    Stock google("GOOG", 135.75);

    std::cout << "--- Copying and Moving ---\n";
    Stock copyApple = apple;              // copy constructor
    Stock movedTesla = std::move(tesla);  // move constructor

    std::cout << "--- Using member functions ---\n";
    apple.setPrice(190.0);
    apple.updatePrice(5.0);
    apple.addQuantity(10);
    apple.display();

    std::cout << "Is Apple expensive (>200)? "
              << (apple.isExpensive(200.0) ? "Yes" : "No") << "\n";

    std::cout << "\n--- Trader Scenario ---\n";
    Trader trader("Alice", 2000.0);
    trader.buyStock(apple, 5);
    trader.buyStock(google, 3);
    trader.displayPortfolio();

    trader.sellStock("AAPL", 2, 210.0);
    trader.displayPortfolio();

    std::cout << "\n--- End of Program ---\n";
    return 0;
}


/*#include <iostream>
#include <vector>
#include <string>

class Stock {
private:
    std::string name;
    double price;

public:
    // --- Constructors ---
    Stock() : name("Unknown"), price(0.0) { // default constructor
        std::cout << "Stock default constructed.\n";
    }

    explicit Stock(const std::string& n, double p = 0.0)
        : name(n), price(p) { // initialization constructor
        std::cout << "Stock initialized with values.\n";
    }

    Stock(const Stock& other) { // copy constructor
        name = other.name;
        price = other.price;
        std::cout << "Stock copy constructed.\n";
    }

    Stock& operator=(const Stock& other) { // copy assignment
        if (this != &other) {
            name = other.name;
            price = other.price;
        }
        std::cout << "Stock copy assigned.\n";
        return *this;
    }

    Stock(Stock&& other) noexcept { // move constructor
        name = std::move(other.name);
        price = other.price;
        std::cout << "Stock move constructed.\n";
    }

    Stock& operator=(Stock&& other) noexcept { // move assignment
        if (this != &other) {
            name = std::move(other.name);
            price = other.price;
        }
        std::cout << "Stock move assigned.\n";
        return *this;
    }

    ~Stock() { // destructor
        std::cout << "Stock destroyed.\n";
    }

    // --- Getters and Setters ---
    const std::string& getName() const { return name; }
    double getPrice() const { return price; }

    void setPrice(double p) {
        if (p > 0)
            price = p;
    }

    // --- Public Member Functions ---
    void updatePrice(double percentChange) {
        price *= (1 + percentChange / 100);
    }

    void display() const {
        std::cout << "Stock: " << name << " | Price: " << price << "\n";
    }

    bool isExpensive(double threshold) const {
        return price > threshold;
    }

    // --- Operator Overload ---
    friend std::ostream& operator<<(std::ostream& os, const Stock& s) {
        os << "Stock(" << s.name << ", " << s.price << ")";
        return os;
    }
};


class Portfolio {
private:
    std::vector<Stock> stocks;

public:
    Portfolio() = default; // default constructor
    Portfolio(const Portfolio&) = default; // copy constructor
    Portfolio& operator=(const Portfolio&) = default; // copy assignment
    ~Portfolio() = default; // destructor

    // Delete move constructor just to demonstrate `= delete`
    Portfolio(Portfolio&&) = delete;
    Portfolio& operator=(Portfolio&&) = delete;

    // Add stock (composition)
    void addStock(const Stock& s) {
        stocks.push_back(s);
    }

    double totalValue() const {
        double sum = 0;
        for (const auto& s : stocks)
            sum += s.getPrice();
        return sum;
    }

    void showAll() const {
        for (const auto& s : stocks)
            std::cout << s << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Portfolio& p) {
        os << "Portfolio(total stocks: " << p.stocks.size() << ")";
        return os;
    }
};


int main() {
    std::cout << "--- Creating Stocks ---\n";
    Stock apple("AAPL", 180.5);
    Stock tesla("TSLA", 250.0);

    std::cout << "--- Copying and Moving ---\n";
    Stock copyApple = apple;            // copy constructor
    Stock movedTesla = std::move(tesla); // move constructor

    std::cout << "--- Using *this and member functions ---\n";
    apple.setPrice(190.0);
    apple.updatePrice(5.0); // increase by 5%
    apple.display();

    std::cout << "Is Apple expensive (>200)? " 
              << (apple.isExpensive(200.0) ? "Yes" : "No") << "\n";

    std::cout << "--- Portfolio Usage ---\n";
    Portfolio myPortfolio;
    myPortfolio.addStock(apple);
    myPortfolio.addStock(copyApple);
    myPortfolio.addStock(movedTesla);

    std::cout << myPortfolio << "\n";
    myPortfolio.showAll();
    std::cout << "Total portfolio value: " << myPortfolio.totalValue() << "\n";

    return 0;
} */











/*#include <iostream>
#include <array>

int main() {
    std::cout << "Hello, world!\n";
    std::array<int, 100> v{};
    int nr;
    int a = 0;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
} */

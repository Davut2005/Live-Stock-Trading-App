#include <iostream>
#include <memory>

#include "./includes/StockFactory.h"
#include "./includes/CryptoStock.h"
#include "./includes/EnergyStock.h"
#include "./includes/HealthStock.h"
#include "./includes/Portfolio.h"
#include "./includes/TechStock.h"
#include "./includes/Trader.h"

#include "./exceptions/StockErrors.h"
#include "./exceptions/StockException.h"

int main() {

  std::vector<std::unique_ptr<Stock>> stocks;

  std::cout << "--- Creating Tech Stocks ---\n";
  auto apple = std::make_unique<TechStock>("AAPL", 180.5);
  stocks.push_back(apple->clone());
  auto google = std::make_unique<TechStock>("GOOG", 135.75);

  std::cout << "--- Creating Crypto Stocks ---\n";
  auto bitcoin = std::make_unique<CryptoStock>("BTC", 30000.0);
  auto ethereum = std::make_unique<CryptoStock>("ETH", 1900.0);

  std::cout << "--- Creating Energy Stocks ---\n";
  auto exxon = std::make_unique<EnergyStock>("XOM", 110.0);
  auto chevron = std::make_unique<EnergyStock>("CVX", 160.0);

  std::cout << "--- Creating Health Stock ---\n";
  auto pfizer = std::make_unique<HealthStock>("PFE", 45);

  auto msft = StockFactory::create("tech", "MSFT", 420.50, 8);
  auto sol = StockFactory::create("crypto", "SOL", 145.20, 20);
  auto xom = StockFactory::create("energy", "XOM", 113.40, 15);

  Portfolio p;

  p.addStock(std::move(msft));
  p.addStock(std::move(sol));
  p.addStock(std::move(xom));

  p.addStock(std::make_unique<TechStock>("AAPL_P", 180));
  p.addStock(std::make_unique<CryptoStock>("BTC_P", 30000));

  p.addStock(std::move(pfizer));

  p.showAll();
  p.showTechStocks();

  std::cout << "\n--- Using Member Functions ---\n";
  apple->addQuantity(10);
  apple->updatePrice(5.0);
  apple->display();

  bitcoin->addQuantity(2);
  bitcoin->updatePrice(10.0);
  bitcoin->display();

  exxon->addQuantity(15);
  exxon->updatePrice(3.0);
  exxon->display();

  std::cout << "\n--- Trader Scenario ---\n";
  Trader trader("Alice", 50000.0);

  try {
    auto expensiveStock = std::make_unique<TechStock>("AAPL", 100);
    trader.buyStock(std::move(expensiveStock), 1);
  } catch (const InvalidPriceException &e) {
    std::cout << "Price error: " << e.what() << "\n";
  } catch (const InvalidQuantityException &e) {
    std::cout << "Quantity error: " << e.what() << "\n";
  } catch (const InsufficientBalanceException &e) {
    std::cout << "Balance error: " << e.what() << "\n";
  } catch (const StockException &e) {
    std::cout << "Stock error: " << e.what() << "\n";
  } catch (const std::exception &e) {
    std::cout << "Other error: " << e.what() << "\n";
  }

  trader.buyStock(std::move(apple), 5);
  trader.buyStock(std::move(google), 3);
  trader.buyStock(std::move(bitcoin), 1);
  trader.buyStock(std::move(ethereum), 1);
  trader.buyStock(std::move(exxon), 5);
  trader.buyStock(std::move(chevron), 4);

  trader.display();

  trader.sellStock("AAPL", 2, 210.0);
  trader.sellStock("BTC", 1, 32000.0);

  trader.display();

  std::cout << "\n--- End of Program ---\n";
  return 0;
}


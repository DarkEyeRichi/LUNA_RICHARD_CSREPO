#include "Store.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    template <typename Number>
    bool ReadNumber(const std::string& prompt, Number& value, Number minimum, Number maximum)
    {
        std::string line;
        while (true)
        {
            std::cout << prompt;
            if (!std::getline(std::cin, line))
                return false;
            std::istringstream input(line);
            char extra;
            if ((input >> value) && !(input >> extra)
                && std::isfinite(value) && value >= minimum && value <= maximum)
                return true;
            std::cout << "Enter a number from " << minimum << " to " << maximum
                      << " with no extra characters.\n";
        }
    }
}

int main()
{
    Store store;
    std::mt19937 generator(std::random_device{}());
    std::cout << "REALISTIC STORE SIMULATOR\n"
              << "Grow your store toward $1,000 cash. Restock, set prices, and open for a day.\n"
              << "Prices are entered in dollars. Choose Help for costs and controls.\n";
    while (true)
    {
        std::cout << '\n';
        store.DisplayBalance();
        std::cout << "1. View inventory\n2. Purchase stock\n3. Sell products\n"
                  << "4. Change shelf price / discount\n5. Transaction history\n"
                  << "6. Finances\n7. Staff and security\n8. Open for one day\n9. Help\n0. Exit\n";
        int choice;
        if (!ReadNumber("Choose (0-9): ", choice, 0, 9) || choice == 0)
            break;
        if (choice == 1)
            store.DisplayInventory();
        else if (choice == 5)
            store.DisplayHistory();
        else if (choice == 6)
            store.DisplayFinances();
        else if (choice == 7)
        {
            store.DisplayStaff();
            int action;
            if (!ReadNumber("1 Hire | 2 Fire | 3 Install security | 0 Back: ", action, 0, 3))
                break;
            if (action == 1) store.HireEmployee();
            else if (action == 2) store.FireEmployee();
            else if (action == 3) store.BuySecurity();
        }
        else if (choice == 8)
        {
            store.DisplayFinances();
            int confirmation;
            if (!ReadNumber("Open for one day? 1 Yes | 0 Cancel: ", confirmation, 0, 1))
                break;
            if (confirmation == 1)
                store.AdvanceDay(generator);
        }
        else if (choice == 9)
        {
            std::cout << "\n=== HOW TO PLAY ===\n"
                      << "Start with $500 and six grocery products. Aim for $1,000 cash.\n"
                      << "Restocking spends wholesale cost. Selling receives the shelf price.\n"
                      << "Discounts increase daily demand. Very high prices can stop sales.\n"
                      << "Opening a day sells to customers and costs $10 rent plus staff/security.\n"
                      << "Employees cost $25 to hire and $5/day, with $15 severance to fire.\n"
                      << "Security costs $75 plus $3/day and prevents theft.\n"
                      << "One wholesale price changes each day. Review prices and low-stock notices.\n"
                      << "Use 0 at product/quantity prompts to cancel. Money rounds to the nearest cent.\n";
        }
        else
        {
            store.DisplayInventory();
            int productId;
            if (!ReadNumber("Product ID (0 to cancel): ", productId, 0, 9999))
                break;
            if (productId == 0)
                continue;
            if (choice == 4)
            {
                double price;
                if (!ReadNumber("New shelf price ($0.01-$10,000, 0 to cancel): $", price, 0.0, 10000.0))
                    break;
                if (price != 0)
                    store.ChangePrice(productId, std::lround(price * 100));
            }
            else
            {
                int amount;
                if (!ReadNumber("Quantity (0 to cancel): ", amount, 0, 10000))
                    break;
                if (amount == 0)
                    continue;
                if (choice == 2)
                    store.PurchaseStock(productId, amount);
                else
                    store.SellProduct(productId, amount);
            }
        }
    }
    std::cout << "Store closed. Thanks for playing!\n";
    return 0;
}

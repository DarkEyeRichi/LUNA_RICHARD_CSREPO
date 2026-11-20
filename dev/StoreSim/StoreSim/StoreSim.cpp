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
    std::cout << "REALISTIC STORE SIMULATOR\n"
              << "Manage groceries, prices, and cash. Prices are entered in dollars.\n";
    while (true)
    {
        std::cout << '\n';
        store.DisplayBalance();
        std::cout << "1. View inventory\n2. Purchase stock\n3. Sell products\n"
                  << "4. Change shelf price / discount\n5. Transaction history\n0. Exit\n";
        int choice;
        if (!ReadNumber("Choose (0-5): ", choice, 0, 5) || choice == 0)
            break;
        if (choice == 1)
            store.DisplayInventory();
        else if (choice == 5)
            store.DisplayHistory();
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
                if (!ReadNumber("New shelf price ($0.01-$10,000): $", price, 0.01, 10000.0))
                    break;
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

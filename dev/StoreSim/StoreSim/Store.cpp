#include "Store.h"
#include <iomanip>
#include <iostream>

Store::Store()
{
    inventory.emplace_back(101, "Milk", 2.00, 3.49, 10);
    inventory.emplace_back(102, "Bread", 1.25, 2.49, 15);
    inventory.emplace_back(103, "Eggs", 2.50, 4.29, 8);
    inventory.emplace_back(104, "Apples", 0.50, 0.99, 25);
    inventory.emplace_back(105, "Rice", 1.75, 3.49, 12);
    inventory.emplace_back(106, "Coffee", 4.00, 6.99, 6);
}

Product* Store::FindProduct(int productId)
{
    for (Product& product : inventory)
    {
        if (product.GetId() == productId)
            return &product;
    }
    return nullptr;
}

void Store::Record(const std::string& description, long long cashChangeCents)
{
    transactions.emplace_back(day, description, cashChangeCents);
    balanceCents += cashChangeCents;
}

void Store::DisplayInventory() const
{
    std::cout << "\n=== GROCERY INVENTORY ===\n"
              << "Wholesale and shelf prices are in dollars.\n"
              << std::left << std::setw(6) << "ID" << std::setw(18) << "Product"
              << std::right << std::setw(12) << "Wholesale"
              << std::setw(12) << "Shelf price" << std::setw(10) << "Quantity"
              << '\n' << std::string(76, '-') << '\n';
    for (const Product& product : inventory)
        product.Display();
}

void Store::DisplayBalance() const
{
    std::cout << std::fixed << std::setprecision(2)
              << "Day " << day << " | Store cash: $" << balanceCents / 100.0 << '\n';
}

void Store::DisplayHistory() const
{
    std::cout << "\n=== TRANSACTION HISTORY ===\n";
    if (transactions.empty())
    {
        std::cout << "No transactions yet. Restock or sell a product to begin.\n";
        return;
    }
    std::cout << std::left << std::setw(7) << "Day" << std::setw(48) << "Action"
              << std::right << std::setw(13) << "Cash change $" << '\n';
    for (const Transaction& transaction : transactions)
        transaction.Display();
}

void Store::PurchaseStock(int productId, int amount)
{
    Product* product = FindProduct(productId);
    if (product == nullptr)
    {
        std::cout << "Product ID not found. Choose an ID from the inventory.\n";
        return;
    }
    if (amount <= 0 || amount > 10000 - product->GetQuantity())
    {
        std::cout << "Quantity must be positive. Each product can hold up to 10,000 units.\n";
        return;
    }
    long long cost = 1LL * product->GetPurchaseCostCents() * amount;
    if (cost > balanceCents)
    {
        std::cout << std::fixed << std::setprecision(2)
                  << "Purchase costs $" << cost / 100.0 << ". Available cash: $"
                  << balanceCents / 100.0 << ". Try a smaller quantity.\n";
        return;
    }
    Record("Restock " + std::to_string(amount) + " " + product->GetName(), -cost);
    product->AddStock(amount);
    std::cout << "Stock purchased successfully.\n";
    DisplayBalance();
}

void Store::SellProduct(int productId, int amount)
{
    Product* product = FindProduct(productId);
    if (product == nullptr)
    {
        std::cout << "Product ID not found. Choose an ID from the inventory.\n";
        return;
    }
    if (amount <= 0 || amount > product->GetQuantity())
    {
        std::cout << "Enter a positive quantity up to the available stock ("
                  << product->GetQuantity() << ").\n";
        return;
    }
    long long revenue = 1LL * product->GetSellingPriceCents() * amount;
    Record("Sell " + std::to_string(amount) + " " + product->GetName(), revenue);
    product->RemoveStock(amount);
    std::cout << std::fixed << std::setprecision(2)
              << "Sale complete. Received $" << revenue / 100.0 << ".\n";
    DisplayBalance();
}

void Store::ChangePrice(int productId, int newPriceCents)
{
    Product* product = FindProduct(productId);
    if (product == nullptr)
    {
        std::cout << "Product ID not found. Choose an ID from the inventory.\n";
        return;
    }
    if (newPriceCents < 1 || newPriceCents > 1000000)
    {
        std::cout << "Enter a price between $0.01 and $10,000.00.\n";
        return;
    }
    if (newPriceCents == product->GetSellingPriceCents())
    {
        std::cout << "That is already the shelf price.\n";
        return;
    }
    Record("Price " + product->GetName() + " to " + std::to_string(newPriceCents)
        + " cents", 0);
    product->SetSellingPriceCents(newPriceCents);
    std::cout << std::fixed << std::setprecision(2)
              << "Shelf price updated to $" << newPriceCents / 100.0 << ".\n";
    if (newPriceCents < product->GetPurchaseCostCents())
        std::cout << "This discount is below wholesale cost. Each sale will lose money.\n";
}

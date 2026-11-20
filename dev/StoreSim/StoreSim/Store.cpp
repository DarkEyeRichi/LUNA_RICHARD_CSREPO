#include "Store.h"
#include <algorithm>
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

void Store::DisplayFinances() const
{
    long long received = 0;
    long long spent = 0;
    long long stockValue = 0;
    for (const Transaction& transaction : transactions)
    {
        long long change = transaction.GetCashChangeCents();
        if (change > 0)
            received += change;
        else
            spent -= change;
    }
    for (const Product& product : inventory)
        stockValue += 1LL * product.GetQuantity() * product.GetPurchaseCostCents();

    std::cout << "\n=== STORE FINANCES ===\n";
    DisplayBalance();
    std::cout << std::fixed << std::setprecision(2)
              << "Cash received:       $" << received / 100.0 << '\n'
              << "Cash spent:          $" << spent / 100.0 << '\n'
              << "Net cash flow:       $" << (received - spent) / 100.0 << '\n'
              << "Stock at wholesale:  $" << stockValue / 100.0 << '\n'
              << "Next day's expenses: $"
              << (1000 + employees * 500 + (security ? 300 : 0)) / 100.0 << '\n';
}

void Store::DisplayStaff() const
{
    std::cout << "\n=== STAFF AND SECURITY ===\n"
              << "Employees: " << employees << "/10\n"
              << "Hiring costs $25.00. Each employee earns $5.00 per simulated day.\n"
              << "Employees increase customer demand. Firing costs $15.00 severance.\n"
              << "Security: " << (security ? "ACTIVE" : "NOT INSTALLED") << '\n'
              << "Security costs $75.00 to install and $3.00 per day. It prevents theft.\n";
}

void Store::HireEmployee()
{
    if (employees >= 10)
    {
        std::cout << "The store already has the maximum of 10 employees.\n";
        return;
    }
    if (balanceCents < 2500)
    {
        std::cout << "Hiring requires $25.00. Check your available cash.\n";
        return;
    }
    Record("Hire employee", -2500);
    ++employees;
    std::cout << "Employee hired. Payroll increases by $5.00 per day.\n";
}

void Store::FireEmployee()
{
    if (employees == 0)
    {
        std::cout << "There are no employees to fire.\n";
        return;
    }
    if (balanceCents < 1500)
    {
        std::cout << "Firing requires $15.00 for severance.\n";
        return;
    }
    Record("Employee severance", -1500);
    --employees;
    std::cout << "Employee dismissed. Paid $15.00 severance.\n";
}

void Store::BuySecurity()
{
    if (security)
    {
        std::cout << "Security is already installed.\n";
        return;
    }
    if (balanceCents < 7500)
    {
        std::cout << "Installing security requires $75.00.\n";
        return;
    }
    Record("Install security", -7500);
    security = true;
    std::cout << "Security installed. Theft prevention costs $3.00 per day.\n";
}

void Store::AdvanceDay(std::mt19937& generator)
{
    if (day >= 3650)
    {
        std::cout << "Your store has reached its 3,650-day anniversary!\n"
                  << "You can continue trading, reviewing history, and saving.\n";
        return;
    }
    int expenses = 1000 + employees * 500 + (security ? 300 : 0);
    if (balanceCents < expenses)
    {
        std::cout << std::fixed << std::setprecision(2)
                  << "Reserve $" << expenses / 100.0
                  << " for rent, payroll, and security before opening.\n"
                  << "You can sell stock manually to raise cash.\n";
        return;
    }

    std::cout << "\n=== DAY " << day << " CUSTOMER SALES ===\n";
    std::uniform_int_distribution<int> demandRoll(1, 6);
    for (Product& product : inventory)
    {
        // Higher shelf prices reduce demand. Employees increase potential customers.
        int demand = (demandRoll(generator) + employees)
            * product.GetPurchaseCostCents() * 2 / product.GetSellingPriceCents();
        int sold = std::min({demand, product.GetQuantity(), 30});
        if (sold > 0)
            SellProduct(product.GetId(), sold);
    }
    Record("Rent", -1000);
    if (employees > 0)
        Record("Daily payroll", -employees * 500);
    if (security)
        Record("Security service", -300);

    std::uniform_int_distribution<int> eventRoll(0, 3);
    std::uniform_int_distribution<int> productRoll(0, 5);
    if (!security && eventRoll(generator) == 0)
    {
        Product& target = inventory[productRoll(generator)];
        if (target.GetQuantity() > 0)
        {
            Record("Theft: 1 " + target.GetName(), 0);
            target.RemoveStock(1);
            std::cout << "Theft reported: one " << target.GetName() << " lost.\n";
        }
    }

    Product& marketProduct = inventory[productRoll(generator)];
    int oldCost = marketProduct.GetPurchaseCostCents();
    int change = std::max(1, oldCost / 10);
    int newCost = oldCost + (eventRoll(generator) < 2 ? -change : change);
    newCost = std::clamp(newCost, 1, 1000000);
    Record("Wholesale change: " + marketProduct.GetName(), 0);
    marketProduct.SetPurchaseCostCents(newCost);
    std::cout << std::fixed << std::setprecision(2)
              << "Wholesale update: " << marketProduct.GetName() << " is now $"
              << newCost / 100.0 << " per unit. Shelf prices stay as you set them.\n"
              << "Paid daily expenses of $" << expenses / 100.0 << ".\n";
    ++day;
    DisplayBalance();
    if (balanceCents >= 100000)
        std::cout << "Store milestone reached: at least $1,000.00 in cash!\n";
}

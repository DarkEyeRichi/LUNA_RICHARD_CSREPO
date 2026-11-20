#include "Store.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

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
    unsavedChanges = true;
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

bool Store::HasUnsavedChanges() const
{
    return unsavedChanges;
}

bool Store::Save(const std::filesystem::path& filename)
{
    if (transactions.size() > 100000)
    {
        std::cout << "Save limit reached (100,000 transactions). Your current session is still available.\n";
        return false;
    }
    std::filesystem::path temporary = filename;
#ifdef _WIN32
    temporary += "." + std::to_string(GetCurrentProcessId()) + ".tmp";
#else
    temporary += ".tmp";
#endif
    std::ofstream file(temporary, std::ios::trunc);
    if (!file)
    {
        std::cout << "Cannot create the save file. Check the folder's write permissions.\n";
        return false;
    }

    file << "STORESIM 1\n" << day << ' ' << balanceCents << ' '
         << employees << ' ' << security << '\n' << inventory.size() << '\n';
    for (const Product& product : inventory)
    {
        file << product.GetId() << ' ' << std::quoted(product.GetName()) << ' '
             << product.GetPurchaseCostCents() << ' ' << product.GetSellingPriceCents()
             << ' ' << product.GetQuantity() << '\n';
    }
    file << transactions.size() << '\n';
    for (const Transaction& transaction : transactions)
    {
        file << transaction.GetDay() << ' ' << std::quoted(transaction.GetDescription())
             << ' ' << transaction.GetCashChangeCents() << '\n';
    }
    file.close();
    std::error_code error;
    if (!file)
    {
        std::filesystem::remove(temporary, error);
        std::cout << "Save failed while writing. The previous save was preserved.\n";
        return false;
    }

    // Replace the previous save only after the new file has been completely written.
#ifdef _WIN32
    bool replaced = MoveFileExW(temporary.c_str(), filename.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    std::filesystem::rename(temporary, filename, error);
    bool replaced = !error;
#endif
    if (!replaced)
    {
        std::filesystem::remove(temporary, error);
        std::cout << "Cannot replace the save file. Check permissions or close programs using it.\n";
        return false;
    }
    unsavedChanges = false;
    std::cout << "Store saved successfully.\n";
    return true;
}

bool Store::Load(const std::filesystem::path& filename)
{
    std::error_code sizeError;
    auto bytes = std::filesystem::file_size(filename, sizeError);
    if (!sizeError && bytes > 16 * 1024 * 1024)
    {
        std::cout << "Save file is too large. Your current store was preserved.\n";
        return false;
    }
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "No readable save file was found. Save a store first.\n";
        return false;
    }
    auto invalid = []()
    {
        std::cout << "Save file is damaged or unsupported. Your current store was preserved.\n";
        return false;
    };

    std::string signature;
    int version;
    if (!(file >> signature >> version) || signature != "STORESIM" || version != 1)
        return invalid();

    // Parse and validate a separate store before replacing the active game.
    Store loaded;
    int savedSecurity;
    if (!(file >> loaded.day >> loaded.balanceCents >> loaded.employees >> savedSecurity)
        || loaded.day < 1 || loaded.day > 3650 || loaded.balanceCents < 0
        || loaded.employees < 0 || loaded.employees > 10
        || (savedSecurity != 0 && savedSecurity != 1))
        return invalid();
    loaded.security = savedSecurity == 1;

    int productCount;
    if (!(file >> productCount) || productCount != 6)
        return invalid();

    for (Product& product : loaded.inventory)
    {
        int id, cost, price, quantity;
        std::string name;
        if (!(file >> id) || (file >> std::ws).peek() != '"'
            || !(file >> std::quoted(name) >> cost >> price >> quantity)
            || id != product.GetId() || name != product.GetName()
            || cost < 1 || cost > 1000000 || price < 1 || price > 1000000
            || quantity < 0 || quantity > 10000)
            return invalid();
        product.SetPurchaseCostCents(cost);
        product.SetSellingPriceCents(price);
        product.RemoveStock(product.GetQuantity());
        product.AddStock(quantity);
    }

    int transactionCount;
    if (!(file >> transactionCount) || transactionCount < 0 || transactionCount > 100000)
        return invalid();
    loaded.transactions.reserve(transactionCount);
    long long expectedBalance = 50000;
    int previousDay = 1;
    for (int index = 0; index < transactionCount; ++index)
    {
        int transactionDay;
        std::string description;
        long long change;
        if (!(file >> transactionDay) || (file >> std::ws).peek() != '"'
            || !(file >> std::quoted(description) >> change)
            || transactionDay < previousDay || transactionDay > loaded.day
            || description.empty() || description.size() > 100
            || change < -10000000000LL || change > 10000000000LL)
            return invalid();
        for (char character : description)
        {
            if (character < ' ' || character > '~')
                return invalid();
        }
        expectedBalance += change;
        if (expectedBalance < 0)
            return invalid();
        loaded.transactions.emplace_back(transactionDay, description, change);
        previousDay = transactionDay;
    }
    file >> std::ws;
    if (!file.eof() || expectedBalance != loaded.balanceCents)
        return invalid();

    *this = std::move(loaded);
    std::cout << "Store loaded successfully.\n";
    DisplayBalance();
    return true;
}

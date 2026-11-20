#pragma once
#include "Product.h"
#include "Transaction.h"
#include <filesystem>
#include <random>
#include <vector>

class Store
{
private:
    std::vector<Product> inventory;
    std::vector<Transaction> transactions;
    long long balanceCents = 50000;
    int day = 1;
    int employees = 0;
    bool security = false;
    bool unsavedChanges = false;

    Product* FindProduct(int productId);
    void Record(const std::string& description, long long cashChangeCents);

public:
    Store();
    void DisplayInventory() const;
    void DisplayBalance() const;
    void DisplayHistory() const;
    void PurchaseStock(int productId, int amount);
    void SellProduct(int productId, int amount);
    void ChangePrice(int productId, int newPriceCents);
    void DisplayFinances() const;
    void DisplayStaff() const;
    void HireEmployee();
    void FireEmployee();
    void BuySecurity();
    void AdvanceDay(std::mt19937& generator);
    bool HasUnsavedChanges() const;
    bool Save(const std::filesystem::path& filename);
    bool Load(const std::filesystem::path& filename);
};

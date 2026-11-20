#pragma once
#include "Product.h"
#include "Transaction.h"
#include <vector>

class Store
{
private:
    std::vector<Product> inventory;
    std::vector<Transaction> transactions;
    long long balanceCents = 50000;
    int day = 1;

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
};

#pragma once
#include <string>

class Product
{
private:
    int id;
    std::string name;
    int purchaseCostCents;
    int sellingPriceCents;
    int quantity;

public:
    Product(int id, const std::string& name, double purchaseCost,
        double sellingPrice, int quantity);
    int GetId() const;
    const std::string& GetName() const;
    int GetPurchaseCostCents() const;
    int GetSellingPriceCents() const;
    int GetQuantity() const;
    void AddStock(int amount);
    void RemoveStock(int amount);
    void SetSellingPriceCents(int price);
    void SetPurchaseCostCents(int cost);
    void Display() const;
};

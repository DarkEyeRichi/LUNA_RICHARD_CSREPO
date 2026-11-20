#include "Product.h"
#include <cmath>
#include <iomanip>
#include <iostream>

Product::Product(int id, const std::string& name, double purchaseCost,
    double sellingPrice, int quantity)
    : id(id), name(name), purchaseCostCents(std::lround(purchaseCost * 100)),
      sellingPriceCents(std::lround(sellingPrice * 100)), quantity(quantity)
{
}

int Product::GetId() const { return id; }
const std::string& Product::GetName() const { return name; }
int Product::GetPurchaseCostCents() const { return purchaseCostCents; }
int Product::GetSellingPriceCents() const { return sellingPriceCents; }
int Product::GetQuantity() const { return quantity; }
void Product::AddStock(int amount) { quantity += amount; }
void Product::RemoveStock(int amount) { quantity -= amount; }
void Product::SetSellingPriceCents(int price) { sellingPriceCents = price; }
void Product::SetPurchaseCostCents(int cost) { purchaseCostCents = cost; }

void Product::Display() const
{
    std::cout << std::left << std::setw(6) << id << std::setw(18) << name
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(12) << purchaseCostCents / 100.0
              << std::setw(12) << sellingPriceCents / 100.0
              << std::setw(10) << quantity;
    if (quantity == 0)
        std::cout << "  OUT OF STOCK";
    else if (quantity <= 5)
        std::cout << "  LOW STOCK";
    std::cout << '\n';
}

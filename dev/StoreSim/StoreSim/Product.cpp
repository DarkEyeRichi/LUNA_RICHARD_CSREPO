#include "Product.h"
#include <iostream>
#include <iomanip>

Product::Product(
    int _id,
    const std::string& _name,
    double _purchaseCost,
    double _sellingPrice,
    int _quantity)
{
    id = _id;
    name = _name;
    purchaseCost = _purchaseCost;
    sellingPrice = _sellingPrice;
    quantity = _quantity;
}

void Product::Display() const
{
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "ID: " << id << '\n';
    std::cout << "Name: " << name << '\n';
    std::cout << "Purchase cost: $" << purchaseCost << '\n';
    std::cout << "Selling price: $" << sellingPrice << '\n';
    std::cout << "Quantity: " << quantity << '\n';
    std::cout << "-------------------------\n";
}
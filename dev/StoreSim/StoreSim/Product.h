#pragma once

#include <string>

class Product
{
private:
	int id;
	std::string name;
	double purchaseCost;
	double sellingPrice;
	int quantity;

public:
	Product(int _id, const std::string& _name, double _purchaseCost, double _sellingPrice, int _quantity);

	void Display() const;
};
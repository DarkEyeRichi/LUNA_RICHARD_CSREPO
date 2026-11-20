#include "Transaction.h"
#include <iomanip>
#include <iostream>

Transaction::Transaction(int day, const std::string& description,
    long long cashChangeCents)
    : day(day), description(description), cashChangeCents(cashChangeCents)
{
}

int Transaction::GetDay() const { return day; }
const std::string& Transaction::GetDescription() const { return description; }
long long Transaction::GetCashChangeCents() const { return cashChangeCents; }

void Transaction::Display() const
{
    std::cout << std::left << std::setw(7) << day << std::setw(48) << description
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(13) << cashChangeCents / 100.0 << '\n';
}

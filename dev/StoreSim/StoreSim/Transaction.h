#pragma once
#include <string>

class Transaction
{
private:
    int day;
    std::string description;
    long long cashChangeCents;

public:
    Transaction(int day, const std::string& description, long long cashChangeCents);
    int GetDay() const;
    const std::string& GetDescription() const;
    long long GetCashChangeCents() const;
    void Display() const;
};

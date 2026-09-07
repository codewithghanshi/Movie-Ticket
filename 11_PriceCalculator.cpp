#pragma once
#include <vector>
#include <memory>
#include "06_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
public:
    // Compile-time polymorphism: overloaded methods.
    double calculate(const vector<shared_ptr<ShowSeat>>& seats) const {
        double total = 0;
        for (const auto& showSeat : seats) total += priceFor(showSeat->getSeat()->getType());
        return total;
    }

    double calculate(const ShowSeat& seat) const {
        return priceFor(seat.getSeat()->getType());
    }

private:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    double priceFor(SeatType type) const {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }
};

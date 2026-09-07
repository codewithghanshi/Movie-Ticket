#pragma once
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string number;
    SeatType type;

public:
    Seat(string number, SeatType type)
        : number(number), type(type) {}

    string getNumber() const { return number; }
    SeatType getType() const { return type; }

    string getTypeName() const {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};

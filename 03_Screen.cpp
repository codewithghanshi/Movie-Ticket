#pragma once
#include <vector>
#include <memory>
#include <string>
#include "02_Seat.cpp"
using namespace std;

// Composition: Screen creates and owns its physical Seat objects.
class Screen {
private:
    int screenNumber;
    vector<shared_ptr<Seat>> seats;

    void createSeats() {
        // 4 Silver, 4 Gold, 2 Platinum seats.
        for (int i = 1; i <= 4; ++i)
            seats.push_back(make_shared<Seat>("A" + to_string(i), SeatType::SILVER));
        for (int i = 1; i <= 4; ++i)
            seats.push_back(make_shared<Seat>("B" + to_string(i), SeatType::GOLD));
        for (int i = 1; i <= 2; ++i)
            seats.push_back(make_shared<Seat>("C" + to_string(i), SeatType::PLATINUM));
    }

public:
    explicit Screen(int screenNumber) : screenNumber(screenNumber) {
        createSeats();
    }

    int getScreenNumber() const { return screenNumber; }
    const vector<shared_ptr<Seat>>& getSeats() const { return seats; }

    shared_ptr<Seat> findSeat(const string& number) const {
        for (const auto& seat : seats)
            if (seat->getNumber() == number) return seat;
        return nullptr;
    }
};

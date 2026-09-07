#pragma once
#include <memory>
#include <string>
#include "02_Seat.cpp"
using namespace std;

enum class SeatStatus { AVAILABLE, BOOKED };

// Encapsulation: seatStatus is private and changed only through validation methods.
class ShowSeat {
private:
    shared_ptr<Seat> seat;
    SeatStatus status;

public:
    explicit ShowSeat(shared_ptr<Seat> seat)
        : seat(seat), status(SeatStatus::AVAILABLE) {}

    shared_ptr<Seat> getSeat() const { return seat; }
    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    bool bookSeat() {
        if (!isAvailable()) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancelSeat() {
        status = SeatStatus::AVAILABLE;
    }
};

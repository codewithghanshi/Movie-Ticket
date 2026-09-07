#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <sstream>
#include "05_Show.cpp"
#include "07_Customer.cpp"
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

// Encapsulation: booking status and amount are private.
class Booking {
private:
    static int nextBookingId;
    string bookingId;
    shared_ptr<Customer> customer;
    shared_ptr<Show> show;
    vector<shared_ptr<ShowSeat>> seats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(shared_ptr<Customer> customer, shared_ptr<Show> show,
            vector<shared_ptr<ShowSeat>> seats, double totalAmount)
        : customer(customer), show(show), seats(seats),
          totalAmount(totalAmount), status(BookingStatus::PENDING) {
        bookingId = "BK" + to_string(nextBookingId++);
    }

    string getBookingId() const { return bookingId; }
    shared_ptr<Customer> getCustomer() const { return customer; }
    shared_ptr<Show> getShow() const { return show; }
    const vector<shared_ptr<ShowSeat>>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void confirm() { status = BookingStatus::CONFIRMED; }
    void fail() { status = BookingStatus::FAILED; }
    void cancel() { status = BookingStatus::CANCELLED; }
};

int Booking::nextBookingId = 1001;

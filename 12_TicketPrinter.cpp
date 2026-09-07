#pragma once
#include <iostream>
#include <iomanip>
#include "08_Booking.cpp"
using namespace std;

// Single Responsibility: TicketPrinter only formats and prints tickets.
class TicketPrinter {
public:
    void print(const Booking& booking) const {
        auto show = booking.getShow();

        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getBookingId() << "\n";
        cout << "Movie      : " << show->getMovie()->getTitle() << "\n";
        cout << "Screen     : Screen-" << show->getScreen()->getScreenNumber() << "\n";
        cout << "Time       : " << show->getStartTime() << "\n";
        cout << "Seats      : ";
        for (const auto& seat : booking.getSeats())
            cout << seat->getSeat()->getNumber() << " ";
        cout << "\nAmount     : Rs." << fixed << setprecision(2)
             << booking.getTotalAmount() << "\n";
        cout << "Status     : ";
        if (booking.getStatus() == BookingStatus::CONFIRMED) cout << "CONFIRMED";
        else if (booking.getStatus() == BookingStatus::CANCELLED) cout << "CANCELLED";
        else if (booking.getStatus() == BookingStatus::FAILED) cout << "FAILED";
        else cout << "PENDING";
        cout << "\n=========================================\n";
    }
};

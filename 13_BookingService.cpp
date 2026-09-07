#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "04_Cinema.cpp"
#include "08_Booking.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;

// Orchestrator: coordinates booking flow; it does not calculate prices or print tickets.
class BookingService {
private:
    vector<shared_ptr<Movie>> movies;
    vector<shared_ptr<Show>> shows;
    vector<shared_ptr<Booking>> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    shared_ptr<Show> getShowById(int id) const {
        for (const auto& show : shows)
            if (show->getShowId() == id) return show;
        return nullptr;
    }

    void seedData() {
        auto movie1 = make_shared<Movie>("3 Idiots", "Hindi", 170);
        auto movie2 = make_shared<Movie>("Interstellar", "English", 169);
        movies = {movie1, movie2};

        auto cinema = make_shared<Cinema>("Single Screen Cinema");
        cinema->addScreen(1);
        cinema->addScreen(2);

        shows.push_back(make_shared<Show>(1, movie1, cinema->getScreen(1), "06:00 PM"));
        shows.push_back(make_shared<Show>(2, movie1, cinema->getScreen(2), "09:00 PM"));
        shows.push_back(make_shared<Show>(3, movie2, cinema->getScreen(1), "03:00 PM"));
    }

    void listMovies() const {
        cout << "\n--- MOVIES ---\n";
        for (size_t i = 0; i < movies.size(); ++i)
            cout << "[" << i + 1 << "] " << movies[i]->getTitle()
                 << " | " << movies[i]->getLanguage()
                 << " | " << movies[i]->getDuration() << " min\n";
    }

    void listShows(int movieIndex) const {
        cout << "\n--- SHOWS ---\n";
        for (const auto& show : shows) {
            if (show->getMovie() == movies[movieIndex - 1])
                cout << "[" << show->getShowId() << "] Screen-"
                     << show->getScreen()->getScreenNumber()
                     << " | " << show->getStartTime() << "\n";
        }
    }

    shared_ptr<Booking> createBooking() {
        listMovies();
        int movieChoice;
        cout << "Choose movie: ";
        if (!(cin >> movieChoice) || movieChoice < 1 ||
            movieChoice > static_cast<int>(movies.size())) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid movie choice.\n";
            return nullptr;
        }

        listShows(movieChoice);
        int showId;
        cout << "Choose show: ";
        if (!(cin >> showId)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid show choice.\n";
            return nullptr;
        }

        auto show = getShowById(showId);
        if (!show || show->getMovie() != movies[movieChoice - 1]) {
            cout << "Invalid show choice.\n";
            return nullptr;
        }

        show->displaySeats();

        int count;
        cout << "Number of seats: ";
        if (!(cin >> count) || count < 1 || count > 10) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid seat count.\n";
            return nullptr;
        }

        vector<shared_ptr<ShowSeat>> selected;
        for (int i = 0; i < count; ++i) {
            string number;
            cout << "Enter seat " << i + 1 << ": ";
            cin >> number;
            auto seat = show->findShowSeat(number);

            if (!seat) {
                cout << "Invalid seat number. Booking rejected.\n";
                return nullptr;
            }
            if (!seat->isAvailable()) {
                cout << "Seat " << number << " is already BOOKED. Booking rejected.\n";
                return nullptr;
            }
            if (find(selected.begin(), selected.end(), seat) != selected.end()) {
                cout << "Seat selected twice. Booking rejected.\n";
                return nullptr;
            }
            selected.push_back(seat);
        }

        double total = priceCalculator.calculate(selected);
        cout << "TOTAL: Rs." << total << "\n";

        int method;
        cout << "Pay by: 1.UPI  2.Card  3.Cash  4.Test Failed Payment\nChoose: ";
        cin >> method;

        unique_ptr<Payment> payment;
        if (method == 1) payment = make_unique<UpiPayment>();
        else if (method == 2) payment = make_unique<CardPayment>();
        else if (method == 3) payment = make_unique<CashPayment>();
        else if (method == 4) payment = make_unique<FailedPayment>();
        else {
            cout << "Invalid payment choice. Booking rejected.\n";
            return nullptr;
        }

        // Booking and payment are created only after validation of selected seats.
        for (const auto& seat : selected) seat->bookSeat();

        auto customer = make_shared<Customer>("Guest Customer", "9999999999");
        auto booking = make_shared<Booking>(customer, show, selected, total);

        // Runtime polymorphism: Payment* calls the selected child implementation.
        bool isPaid = payment->pay(total);

        if (isPaid) {
            booking->confirm();
            bookings.push_back(booking);
            ticketPrinter.print(*booking);
            return booking;
        }

        // Failed payment: release all seats and do not confirm booking.
        for (const auto& seat : selected) seat->cancelSeat();
        booking->fail();
        cout << "Booking failed. Seats have been released.\n";
        return nullptr;
    }

    void cancelBooking() {
        string id;
        cout << "Enter Booking ID: ";
        cin >> id;

        for (const auto& booking : bookings) {
            if (booking->getBookingId() == id) {
                if (booking->getStatus() != BookingStatus::CONFIRMED) {
                    cout << "Booking cannot be cancelled.\n";
                    return;
                }
                for (const auto& seat : booking->getSeats()) seat->cancelSeat();
                booking->cancel();
                cout << "Booking cancelled. Seats are AVAILABLE again.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void showTickets() const {
        if (bookings.empty()) {
            cout << "No confirmed bookings.\n";
            return;
        }
        for (const auto& booking : bookings) ticketPrinter.print(*booking);
    }

public:
    BookingService() { seedData(); }

    void run() {
        int choice;
        do {
            cout << "\n===== MOVIE TICKET BOOKING =====\n";
            cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
            cout << "Choose: ";
            if (!(cin >> choice)) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Invalid choice. Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1: listMovies(); break;
                case 2: createBooking(); break;
                case 3: cancelBooking(); break;
                case 4: showTickets(); break;
                case 0: cout << "Thank you!\n"; break;
                default: cout << "Invalid menu choice.\n";
            }
        } while (choice != 0);
    }
};

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

// Aggregation: a Show refers to an existing Movie.
// Association: a Show uses a Screen.
// Composition: Show creates/owns ShowSeat objects for this screening.
class Show {
private:
    int showId;
    shared_ptr<Movie> movie;
    shared_ptr<Screen> screen;
    string startTime;
    vector<shared_ptr<ShowSeat>> showSeats;

    void createShowSeats() {
        for (const auto& seat : screen->getSeats())
            showSeats.push_back(make_shared<ShowSeat>(seat));
    }

public:
    Show(int showId, shared_ptr<Movie> movie, shared_ptr<Screen> screen,
         string startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        createShowSeats();
    }

    int getShowId() const { return showId; }
    shared_ptr<Movie> getMovie() const { return movie; }
    shared_ptr<Screen> getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    const vector<shared_ptr<ShowSeat>>& getShowSeats() const { return showSeats; }

    shared_ptr<ShowSeat> findShowSeat(const string& number) const {
        for (const auto& showSeat : showSeats)
            if (showSeat->getSeat()->getNumber() == number) return showSeat;
        return nullptr;
    }

    void displaySeats() const {
        cout << "\nSCREEN-" << screen->getScreenNumber()
             << "  " << startTime << "  |  " << movie->getTitle() << "\n";
        cout << "([ ] = AVAILABLE, [X] = BOOKED)\n\n";
        cout << "SILVER: ";
        for (const auto& s : showSeats)
            if (s->getSeat()->getType() == SeatType::SILVER)
                cout << s->getSeat()->getNumber() << (s->isAvailable() ? "[ ] " : "[X] ");
        cout << "\nGOLD:   ";
        for (const auto& s : showSeats)
            if (s->getSeat()->getType() == SeatType::GOLD)
                cout << s->getSeat()->getNumber() << (s->isAvailable() ? "[ ] " : "[X] ");
        cout << "\nPLATINUM: ";
        for (const auto& s : showSeats)
            if (s->getSeat()->getType() == SeatType::PLATINUM)
                cout << s->getSeat()->getNumber() << (s->isAvailable() ? "[ ] " : "[X] ");
        cout << "\n";
    }
};

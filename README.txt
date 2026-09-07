MOVIE TICKET BOOKING SYSTEM - TCS-504 ASSIGNMENT 1

Files:
01_Movie.cpp
02_Seat.cpp
03_Screen.cpp
04_Cinema.cpp
05_Show.cpp
06_ShowSeat.cpp
07_Customer.cpp
08_Booking.cpp
09_Payment.cpp
10_PaymentTypes.cpp
11_PriceCalculator.cpp
12_TicketPrinter.cpp
13_BookingService.cpp
main.cpp

Compile (g++):
g++ -std=c++17 main.cpp -o movie_booking

Run:
./movie_booking

Important:
Because the assignment says "one class per file" and "no header files", main.cpp includes
the class modules in dependency order. Compile main.cpp only.

Required edge-case demo:
1. Book A1 -> succeeds.
2. Try A1 again -> rejected as already BOOKED.
3. Choose another available seat and select "4. Test Failed Payment" -> payment fails and seat becomes AVAILABLE.
4. Make a successful booking, note the Booking ID, then use Cancel -> seats become AVAILABLE.
5. Enter invalid menu/seat -> clear error and no crash.

OOP concepts are marked in comments inside the relevant files.

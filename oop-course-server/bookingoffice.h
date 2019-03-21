#ifndef BOOKINGOFFICE_H
#define BOOKINGOFFICE_H
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <algorithm>
#include <windows.h>

#include "events.h"
#include "exponentialdelayer.h"


using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::duration;


class TicketWindow;
class BookingOffice;
class Customer;

class Cashier
{
    ExponentialDelayer delayer;
public:
    Cashier(double mean);

    void sellTicket(Customer & c);

    void setNewMean(double mean);
};

class Customer
{
private:
    class BookingOffice & targetOffice;
public:
    Customer(BookingOffice & targetOffice);
    void chooseWindow();
};


class TicketWindow: public EventsPublisher
{
private:
    high_resolution_clock::time_point lastCall;
    std::vector<milliseconds> serveTime;
    std::queue<Customer *> customerQueue;
    Cashier & cashier;
public:
    TicketWindow(Cashier & c);
    Customer * getNextCustomer();
    size_t getQueueLength() const;
    void getInQueue(Customer & c);
    void loadServeTimeStats(std::vector<milliseconds> & buffer);
    Cashier * getCashier();
    void sellTicket();
    void work();
    void synchronizeStatistics();
};


class BookingOffice
{
private:
    std::vector<TicketWindow *> windows;

public:
    BookingOffice();
    void openNewWindow(Cashier & c);
    std::vector<TicketWindow *> getWindows();
};

#endif // BOOKINGOFFICE_H

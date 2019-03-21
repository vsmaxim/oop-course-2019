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


class TicketWindow;
class BookingOffice;
class Customer;

class Cashier
{
    ExponentialDelayer delayer;
public:
    Cashier(double mean);
    Cashier(Cashier && other) = default;
    Cashier& operator=(Cashier && other) = default;

    int sellTicket(Customer & c);

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
    std::vector<int> serveTime;
    std::queue<Customer *> customerQueue;
    Cashier & cashier;
public:
    TicketWindow(Cashier & c);

    Customer * getNextCustomer();
    size_t getQueueLength() const;
    void getInQueue(Customer & c);

    void loadServeTimeStats(std::vector<int> & buffer);
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

#include "bookingoffice.h"


Cashier::Cashier(double mean) : delayer(mean)
{

}

void Cashier::sellTicket(Customer &c)
{
    delayer.delay();
    cout << "Sold ticket to: " << &c << endl;
}

void Cashier::setNewMean(double mean)
{
    delayer.setNewMean(mean);
}


BookingOffice::BookingOffice() : windows{}
{

}


void BookingOffice::openNewWindow(Cashier &c)
{
    windows.push_back(new TicketWindow(c));
}


std::vector<TicketWindow *> BookingOffice::getWindows()
{
    return windows;
}


Customer::Customer(BookingOffice & targetOffice) : targetOffice(targetOffice)
{

}


TicketWindow::TicketWindow(Cashier & c) : lastCall(high_resolution_clock::now()), serveTime(),
    customerQueue(), cashier(c)
{

}


Customer * TicketWindow::getNextCustomer()
{
    if (customerQueue.empty())
    {
        return nullptr;
    }
    synchronizeStatistics();
    Customer * customer = customerQueue.front();
    customerQueue.pop();
    return customer;
}

void TicketWindow::synchronizeStatistics()
{
    auto delta = duration_cast<milliseconds>(high_resolution_clock::now() - lastCall);
    serveTime.push_back(delta);
    notify();
}


size_t TicketWindow::getQueueLength() const
{
    return customerQueue.size();
}


void TicketWindow::getInQueue(Customer &c)
{
    customerQueue.push(&c);
}

void TicketWindow::loadServeTimeStats(std::vector<std::chrono::milliseconds> &buffer)
{
    std::move(serveTime.begin(), serveTime.end(), std::back_inserter(buffer));
}

Cashier * TicketWindow::getCashier()
{
    return &cashier;
}

void TicketWindow::sellTicket()
{
    cashier.sellTicket(*getNextCustomer());
}

void TicketWindow::work()
{
    Customer * c = getNextCustomer();
    if (c)
    {
        cashier.sellTicket(*c);
    }
}


void Customer::chooseWindow() {
    std::vector<TicketWindow *> windows = targetOffice.getWindows();
    auto minimalWindow = std::min_element(
                windows.begin(),
                windows.end(),
                [](const TicketWindow * left, const TicketWindow * right) {
                    return left->getQueueLength() < right->getQueueLength();
    });
    (*minimalWindow)->getInQueue(*this);
}

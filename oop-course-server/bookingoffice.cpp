#include "bookingoffice.h"


Cashier::Cashier(double mean) : delayer(mean)
{

}

int Cashier::sellTicket(Customer &c)
{
    int delay = delayer.delay();
    std::cout << "Sold ticket to " << &c << " by cashier " << this << std::endl;
    return delay;
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


TicketWindow::TicketWindow(Cashier & c) : serveTime(), customerQueue(), cashier(c)
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

void TicketWindow::loadServeTimeStats(std::vector<int> &buffer)
{
    std::move(serveTime.begin(), serveTime.end(), std::back_inserter(buffer));
    serveTime.clear();
    std::cout << "ServeTime length: " << serveTime.size() << std::endl;
    for (auto & it: serveTime)
    {
        std::cout << "Element: " << it << std::endl;
    }
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
        int serviceTime = cashier.sellTicket(*c);
        std::cout << "Service time: " << serviceTime << std::endl;
        serveTime.push_back(serviceTime);
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
    if ((*minimalWindow)->getQueueLength() > 3)
    {
        std::cout << "Customer discarded" << std::endl;
        return;
    }
    (*minimalWindow)->getInQueue(*this);
}

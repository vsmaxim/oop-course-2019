#ifndef MODEL_H
#define MODEL_H

#include <thread>
#include <vector>
#include <windows.h>

#include "bookingoffice.h"
#include "customergenerator.h"
#include "statisticscollector.h"

using std::vector;
using std::thread;

class model
{
private:
    bool simulate;
    vector<thread> threads;

    Cashier firstCashier;
    Cashier secondCashier;
    BookingOffice office;
    CustomerGenerator customerGenerator;
    StatisticsCollector collector;

public:
    model(double generatorMean, double firstCashierMean, double secondCashierMean);
    ~model();

    void run();
    void stop();

    void runTicketWindow(TicketWindow * window);
    void runStatisticsCollector();
    void runCustomerGenerator();

    void setCustomerGeneratorMean(double mean);
    void setFirstCustomerMean(double mean);
    void setSecondCustomerMean(double mean);

    double getMeanValueForCustomer(int cashierIndex);
    double getStdValueForCustomer(int cashierIndex);
};

#endif // MODEL_H

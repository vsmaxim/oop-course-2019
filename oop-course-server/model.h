#ifndef MODEL_H
#define MODEL_H

#include <thread>
#include <vector>
#include <windows.h>
#include <memory>

#include "bookingoffice.h"
#include "customergenerator.h"
#include "statisticscollector.h"


class Model
{
private:
    bool simulate;
    std::vector<std::thread> threads;

    std::vector<std::shared_ptr<Cashier>> cashiers;
    BookingOffice office;
    CustomerGenerator customerGenerator;
    StatisticsCollector collector;

public:
    Model(double generatorMean, std::vector<double> cashiersMean);
    ~Model();

    void run();
    void stop();

    void runTicketWindow(TicketWindow * window);
    void runStatisticsCollector();
    void runCustomerGenerator();

    void setCustomerGeneratorMean(double mean);
    void setCashierMean(size_t index, double mean);

    double getMeanValueForCustomer(size_t cashierIndex);
    double getStdValueForCustomer(size_t cashierIndex);
};

#endif // MODEL_H

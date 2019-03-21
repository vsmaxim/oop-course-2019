#include <thread>
#include <memory>
#include <vector>
#include <windows.h>

#include "model.h"
#include "bookingoffice.h"
#include "customergenerator.h"
#include "statisticscollector.h"


model::model(double generatorMean, double firstCashierMean, double secondCashierMean): firstCashier(firstCashierMean),
    secondCashier(secondCashierMean),  office(), customerGenerator(generatorMean), collector()
{
    office.openNewWindow(firstCashier);
    office.openNewWindow(secondCashier);
    for (auto &window: office.getWindows())
    {
        window->subscribe(static_cast<SubscriberInterface *>(&collector));
    }
}

model::~model()
{
    stop();
}

void model::run()
{
    simulate = true;
    for (auto window : office.getWindows())
    {
        threads.emplace_back(&model::runTicketWindow, this, window);
    }
    threads.emplace_back(&model::runCustomerGenerator, this);
    threads.emplace_back(&model::runStatisticsCollector, this);
}

void model::stop()
{
    simulate = false;
    for (auto &thread: threads)
    {
        thread.join();
        cout << "Thread joined\n";
    }
    threads.clear();
}

void model::runTicketWindow(TicketWindow *window)
{
    while (simulate)
    {
        window->work();
    }
}

void model::runCustomerGenerator()
{
    while (simulate)
    {
        Customer c = customerGenerator.generateCustomer(office);
        c.chooseWindow();
    }
}

void model::setCustomerGeneratorMean(double mean)
{
    customerGenerator.setNewMean(mean);
}

void model::setFirstCustomerMean(double mean)
{
    firstCashier.setNewMean(mean);
}

void model::setSecondCustomerMean(double mean)
{
    secondCashier.setNewMean(mean);
}

void model::runStatisticsCollector()
{
    while (simulate)
    {
        Sleep(1000);
        collector.printReport();
    }
}


double model::getMeanValueForCustomer(int cashierIndex)
{
    if (cashierIndex == 1)
    {
        return collector.mean(&firstCashier);
    }
    else if (cashierIndex == 2)
    {
        return collector.mean(&secondCashier);
    }
    return 0;
}


double model::getStdValueForCustomer(int cashierIndex)
{
    if (cashierIndex == 1)
    {
        return collector.std(&firstCashier);
    }
    else if (cashierIndex == 2)
    {
        return collector.std(&secondCashier);
    }
    return 0;
}

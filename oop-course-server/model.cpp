#include <thread>
#include <memory>
#include <vector>
#include <windows.h>
#include <cstdarg>

#include "model.h"
#include "bookingoffice.h"
#include "customergenerator.h"
#include "statisticscollector.h"


Model::Model(double generatorMean, std::vector<double> cashiersMean) : customerGenerator(generatorMean), office(), collector(), cashiers()
{
    for (auto & mean: cashiersMean)
    {
        cashiers.push_back(std::make_shared<Cashier>(mean));
        office.openNewWindow(*cashiers.back());
    }
    for (auto &window: office.getWindows())
    {
        window->subscribe(&collector);
    }
}


Model::~Model()
{
    stop();
}


void Model::run()
{
    simulate = true;
    for (auto window : office.getWindows())
    {
        threads.emplace_back(&Model::runTicketWindow, this, window);
    }
    threads.emplace_back(&Model::runCustomerGenerator, this);
    threads.emplace_back(&Model::runStatisticsCollector, this);
}


void Model::stop()
{
    simulate = false;
    for (auto &thread: threads)
    {
        thread.join();
        std::cout << "Thread joined\n";
    }
    threads.clear();
}


void Model::runTicketWindow(TicketWindow *window)
{
    while (simulate)
    {
        window->work();
    }
}


void Model::runCustomerGenerator()
{
    while (simulate)
    {
        Customer c = customerGenerator.generateCustomer(office);
        c.chooseWindow();
    }
}


void Model::setCustomerGeneratorMean(double mean)
{
    customerGenerator.setNewMean(mean);
}

void Model::setCashierMean(size_t index, double mean)
{
    if (index < cashiers.size())
    {
        cashiers[index]->setNewMean(mean);
    }
}


void Model::runStatisticsCollector()
{
    while (simulate)
    {
        Sleep(1000);
        collector.printReport();
    }
}


double Model::getMeanValueForCustomer(size_t cashierIndex)
{
    if (cashierIndex < cashiers.size())
    {
        return collector.mean(cashiers[cashierIndex].get());
    }
    return 0;
}


double Model::getStdValueForCustomer(size_t cashierIndex)
{
    if (cashierIndex < cashiers.size())
    {
        return collector.std(cashiers[cashierIndex].get());
    }
    return 0;
}

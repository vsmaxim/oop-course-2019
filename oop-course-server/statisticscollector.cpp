#include "statisticscollector.h"

#include <math.h>

double StatisticsCollector::mean(Cashier *ptr)
{
    std::vector<int> vec = map[ptr];
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    return static_cast<double>(sum) / vec.size();
}

double StatisticsCollector::std(Cashier *ptr)
{
    double meanValue = mean(ptr);
    std::vector<int> vec = map[ptr];
    double squaredSum = accumulate(vec.begin(), vec.end(), 0, [meanValue](const double & left, const int & right) {
       return left + pow((right - meanValue), 2);
    });
    return sqrt(squaredSum / (vec.size()));
}

void StatisticsCollector::update(EventsPublisher & object)
{
    TicketWindow * obj = static_cast<TicketWindow *>(&object);
    std::cout << "Load cashier " << obj->getCashier() << "for update\n";
    obj->loadServeTimeStats(map[obj->getCashier()]);
}

void StatisticsCollector::printReport()
{
    for (auto const& x : map)
    {
        std::cout << "Cashier with address: " << x.first << std:: endl;
        std::cout << "Mean: " << mean(x.first) << " " << "STD: " << std(x.first) << std::endl;
        std::cout << std::endl;
    }
}

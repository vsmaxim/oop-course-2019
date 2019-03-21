#include "statisticscollector.h"

#include <math.h>

double StatisticsCollector::mean(Cashier *ptr)
{
    std::vector<milliseconds> vec = map[ptr];
    const int64_t sum = std::accumulate(vec.begin(), vec.end(), 0, [](const int64_t & left, const milliseconds & right){
        return left+ right.count();
    });
    std::cout << "Sum: " << sum << std::endl;
    return static_cast<double>(sum) / vec.size();
}

double StatisticsCollector::std(Cashier *ptr)
{
    double meanValue = mean(ptr);
    std::cout << "Mean value: " << meanValue << std::endl;
    std::vector<milliseconds> vec = map[ptr];
    double squaredSum = accumulate(vec.begin(), vec.end(), 0, [meanValue](const double & left, const milliseconds & right) {
       return left + pow((right.count() - meanValue), 2);
    });
    std::cout << "Squared sum: " << squaredSum << std::endl;
    return squaredSum / (vec.size() - 1);
}

void StatisticsCollector::update(EventsPublisher & object)
{
    TicketWindow * obj = static_cast<TicketWindow *>(&object);
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

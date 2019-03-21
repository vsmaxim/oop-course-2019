#ifndef STATISTICSCOLLECTOR_H
#define STATISTICSCOLLECTOR_H
#include <map>
#include <chrono>
#include <iostream>

#include "events.h"
#include "bookingoffice.h"


class StatisticsCollector : public SubscriberInterface
{
private:
    std::map<Cashier *, std::vector<int>> map;

public:    
    ~StatisticsCollector() override = default;

    void update(EventsPublisher & object) override;

    double mean(Cashier * ptr);
    double std(Cashier * ptr);
    void printReport();

};

#endif // STATISTICSCOLLECTOR_H

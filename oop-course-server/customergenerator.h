#ifndef CUSTOMERGENERATOR_H
#define CUSTOMERGENERATOR_H
#include <iostream>

#include "bookingoffice.h"

class CustomerGenerator
{
private:
    ExponentialDelayer delayer;
public:
    CustomerGenerator(double mean);
    CustomerGenerator(const CustomerGenerator & obj);

    Customer generateCustomer(BookingOffice & office);

    void setNewMean(double mean);
};

#endif // CUSTOMERGENERATOR_H

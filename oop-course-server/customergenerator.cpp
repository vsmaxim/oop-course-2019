#include "customergenerator.h"

CustomerGenerator::CustomerGenerator(double mean) : delayer(mean)
{

}

CustomerGenerator::CustomerGenerator(const CustomerGenerator &obj) : delayer(obj.delayer)
{

}


Customer CustomerGenerator::generateCustomer(BookingOffice & office)
{
    delayer.delay();
    std::cout << "Customer generated" << std::endl;
    return Customer(office);
}

void CustomerGenerator::setNewMean(double mean)
{
    delayer.setNewMean(mean);
}

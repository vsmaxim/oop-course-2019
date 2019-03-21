#include "exponentialdelayer.h"
#include <windows.h>

ExponentialDelayer::ExponentialDelayer(double mean) : sampler(1 / mean), generator()
{

}

ExponentialDelayer::ExponentialDelayer(const ExponentialDelayer &obj) : sampler(obj.sampler), generator()
{

}


void ExponentialDelayer::delay()
{
    DWORD millisecondsToSleep = static_cast<DWORD>(sampler(generator) * 1000);
    Sleep(millisecondsToSleep);
}

void ExponentialDelayer::setNewMean(double newMean)
{
    std::exponential_distribution<double>::param_type newLambda(newMean);
    sampler.param(newLambda);
}





#include "exponentialdelayer.h"
#include <windows.h>
#include <iostream>

ExponentialDelayer::ExponentialDelayer(double mean) : sampler(1 / mean), generator()
{
}

ExponentialDelayer::ExponentialDelayer(const ExponentialDelayer &obj) : sampler(obj.sampler), generator()
{

}


int ExponentialDelayer::delay()
{
    DWORD millisecondsToSleep = static_cast<DWORD>(sampler(generator) * 1000);
    Sleep(millisecondsToSleep);
    return static_cast<int>(millisecondsToSleep);
}

void ExponentialDelayer::setNewMean(double newMean)
{
    std::exponential_distribution<double>::param_type newLambda(1 / newMean);
    sampler.param(newLambda);
}





#ifndef EXPONENTIALDELAYER_H
#define EXPONENTIALDELAYER_H
#include <random>
#include "delayer.h"

class ExponentialDelayer : public Delayer
{
private:
    std::exponential_distribution<double> sampler;
    std::default_random_engine generator;
public:
    ExponentialDelayer(double mean);
    ExponentialDelayer(const ExponentialDelayer & obj);
    ~ExponentialDelayer() override = default;

    int delay() override;
    void setNewMean(double newMean);
};

#endif // EXPONENTIALDELAYER_H

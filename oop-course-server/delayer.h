#ifndef DELAYER_H
#define DELAYER_H


class Delayer
{
public:
    virtual int delay() = 0;
    virtual ~Delayer() {}
};

#endif // DELAYER_H

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "eventpublisher.h"


class Subscriber
{
public:
    Subscriber();
    void update(EventPublisher & obj);
};

#endif // SUBSCRIBER_H

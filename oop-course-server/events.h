#ifndef EVENTS_H
#define EVENTS_H
#include <vector>

class SubscriberInterface;


class EventsPublisher
{
private:
    std::vector<SubscriberInterface *> subscribers;
public:
    EventsPublisher();
    void subscribe(SubscriberInterface * sub);
    void unsubscribe(SubscriberInterface * sub);
    void notify();
};


class SubscriberInterface
{
public:
    virtual void update(EventsPublisher & obj) = 0;
    virtual ~SubscriberInterface() {}
};

#endif // EVENTS_H

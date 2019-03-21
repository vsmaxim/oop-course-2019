#include "events.h"
#include <vector>
#include <algorithm>

EventsPublisher::EventsPublisher() : subscribers{}
{

}

void EventsPublisher::subscribe(SubscriberInterface * sub)
{
    subscribers.push_back(sub);
}

void EventsPublisher::unsubscribe(SubscriberInterface * sub)
{
    auto it = std::find(std::begin(subscribers), std::end(subscribers), sub);
    subscribers.erase(it);
}

void EventsPublisher::notify()
{
    for (auto &subscriber: subscribers)
    {
        subscriber->update(*this);
    }
}

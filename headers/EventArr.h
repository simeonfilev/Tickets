//
// Created by Moni on 04-May-20.
//

#ifndef TICKETS_EVENTARR_H
#define TICKETS_EVENTARR_H

#include <vector>
#include "Event.h"
#include "Date.h"

class EventArr {
private:
    std::vector<Event> events;
    void destroy();
    void copy(const EventArr &other);

public:
    EventArr();
    EventArr(const EventArr &other);
    EventArr &operator=(const EventArr &other);
    ~EventArr();
    EventArr &addEvent(const Event &newEvent);
    int getSize() const;
    bool existsEventOnThisDay(const Event &event);

    const std::vector<Event> &getEvents() const;

    Event* getEventByNameAndDate(Date date, std::string name);

    Event* getEventByDateAndHall(Date date, Hall hall);

    int getEventIndex(const Event &event);

    void getBookedTicketsOnDateWithName(Date date, std::string name);

    int getNumberOfBookedTickets(Event e);

    void getBookedTicketsOnDate(Date date);

    void getBookedTicketsOnName(std::string name);

    void printMostPopularEvents();
};


#endif //TICKETS_EVENTARR_H

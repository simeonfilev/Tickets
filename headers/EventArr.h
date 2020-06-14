//
// Created by Moni on 04-May-20.
//

#ifndef TICKETS_EVENTARR_H
#define TICKETS_EVENTARR_H

#include <vector>
#include "Event.h"
#include "Date.h"

/*! \class EventArr
    \brief Клас който дефинира списък от събития
*/
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

    Event *getEventByNameAndDate(const Date &date, const std::string &name);

    Event *getEventByDateAndHall(const Date &date, const Hall &hall);

    void getBookedTicketsOnDateWithName(const Date &date, const std::string &name);

    int getNumberOfBookedTickets(const Event &e);

    void getBookedTicketsOnDate(const Date &date);

    void getBookedTicketsOnName(const std::string &name);

    void printMostPopularEvents();
};


#endif //TICKETS_EVENTARR_H

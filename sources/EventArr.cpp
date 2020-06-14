//
// Created by Moni on 04-May-20.
//

#include "../headers/EventArr.h"

int EventArr::getSize() const {
    return this->events.size();
}

void EventArr::destroy() {
    delete this;
}

void EventArr::copy(const EventArr &other) {
    for (int i = 0; i < other.getSize(); i++) {
        this->events[i] = other.events[i];
    }
}

EventArr::EventArr() {

}

EventArr::EventArr(const EventArr &other) {
    this->copy(other);
}

EventArr &EventArr::operator=(const EventArr &other) {
    if (this != &other) {
        this->destroy();
        this->copy(other);
    }
    return *this;
}

EventArr::~EventArr() {
    this->destroy();
}

//! adds a event in the event array
EventArr &EventArr::addEvent(const Event &newEvent) {
    if (existsEventOnThisDay(newEvent))
        throw std::invalid_argument("received invalid date");
    this->events.push_back(newEvent);
    return *this;
}

//! returns true if an event already exists on a given date
bool EventArr::existsEventOnThisDay(const Event &event) {
    for (int i = 0; i < this->getSize(); i++) {
        Event e = this->events[i];
        if (e.getDay() == event.getDay()
            && e.getYear() == event.getYear()
            && e.getMonth() == event.getMonth()) {
            return true;
        }
    }
    return false;
}

const std::vector<Event> &EventArr::getEvents() const {
    return events;
}

//! returns true if two dates are the same
bool sameDate(int day, int month, int year, const Event &event) {
    return event.getMonth() == month
           && event.getYear() == year
           && event.getDay() == day;
}

//! returns a event by given date and name
Event *EventArr::getEventByNameAndDate(const Date &date, const std::string &name) {
    for (int i = 0; i < this->getSize(); i++) {
        Event e = this->getEvents()[i];
        if (sameDate(date.getDay(), date.getMonth(), date.getYear(), e) && e.getName() == name) {
            return &this->events[i];
        }
    }
    throw std::invalid_argument("Event not found!");

}

//! return an event by given date and hall
Event *EventArr::getEventByDateAndHall(const Date &date, const Hall &hall) {
    for (int i = 0; i < this->getSize(); i++) {
        Event e = this->getEvents()[i];
        if (sameDate(date.getDay(), date.getMonth(), date.getYear(), e) && (e.getHall() == hall)) {
            return &this->events[i];
        }
    }

    return nullptr;
}

//! prints booked tickets by given name and date
void EventArr::getBookedTicketsOnDateWithName(const Date &date, const std::string &name) {
    for (int i = 0; i < this->getSize(); i++) {
        Event event = this->getEvents()[i];
        if (date == event.getDate()
            && event.getName() == name) {
            std::cout << "Booked tickets: " << std::endl;
            int hallRows = event.getHall().getRows();
            int hallSeats = event.getHall().getSeats();
            for (int j = 1; j <= hallRows; j++) {
                for (int z = 1; z <= hallSeats; z++) {
                    int seatToBook = ((j - 1) * event.getHall().getSeats()) + (z - 1);
                    if (event.getSeats()[seatToBook] == 0) {
                        std::cout << "[" << j << "," << z << "]" << std::endl;
                    }
                }
            }
            return;
        }
    }
    throw std::invalid_argument("Nothing found!");
}

//! returns the number of booked tickets by given event
int EventArr::getNumberOfBookedTickets(const Event &e) {
    int counter = 0;
    for (int i : e.getSeats()) {
        if (i == 0) {
            counter++;
        }

    }
    return counter;
}

//! prints booked tickets by given date
void EventArr::getBookedTicketsOnDate(const Date &date) {
    int day = date.getDay();
    int month = date.getMonth();
    int year = date.getYear();

    for (int i = 0; i < this->getSize(); i++) {
        Event event = this->getEvents()[i];
        if (event.getDay() == day
            && event.getMonth() == month
            && event.getYear() == year) {
            std::cout << "Booked tickets: " << std::endl;
            int hallRows = event.getHall().getRows();
            int hallSeats = event.getHall().getSeats();
            for (int j = 1; j <= hallRows; j++) {
                for (int z = 1; z <= hallSeats; z++) {
                    int seatToBook = ((j - 1) * event.getHall().getSeats()) + (z - 1);
                    if (event.getSeats()[seatToBook] == 0) {
                        std::cout << "[" << j << "," << z << "]" << std::endl;
                    }
                }
            }
            return;
        }
    }
}

//! prints booked tickets by given name
void EventArr::getBookedTicketsOnName(const std::string &name) {
    for (int i = 0; i < this->getSize(); i++) {
        Event event = this->getEvents()[i];
        if (event.getName() == name) {
            std::cout << "Booked tickets: " << std::endl;
            int hallRows = event.getHall().getRows();
            int hallSeats = event.getHall().getSeats();
            for (int j = 1; j <= hallRows; j++) {
                for (int z = 1; z <= hallSeats; z++) {
                    int seatToBook = ((j - 1) * event.getHall().getSeats()) + (z - 1);
                    if (event.getSeats()[seatToBook] == 0) {
                        std::cout << "[" << j << "," << z << "]" << std::endl;
                    }
                }
            }
            return;
        }
    }
}

//! prints the most popular events by sorting them
void EventArr::printMostPopularEvents() {
    std::map<Event, int> map;

    for (int i = 0; i < this->getSize(); i++) {
        Event event = this->getEvents()[i];
        map[event] = event.getBoughtTicketsCount();
    }
    for (const auto &entry : map) {
        std::cout << "Event with name: " << entry.first.getName() << " has sold: " << entry.second << " tickets!"
                  << std::endl;
    }
}






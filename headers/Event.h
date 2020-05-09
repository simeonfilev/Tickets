//
// Created by Moni on 04-May-20.
//
#include <iostream>
#include <vector>
#include "Hall.h"
#include "map"
#include "Date.h"

#ifndef TICKETS_EVENT_H
#define TICKETS_EVENT_H


class Event {
private:
    std::string name;
    Date date;
    Hall hall;
    std::vector<int> seats;
    std::map<std::pair<int, int>, std::string> notes;
public:
    Event();

    Event(std::string name, Hall hall, Date date);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    const std::vector<int> &getSeats() const;

    const Hall getHall() const;

    void setHall(Hall hall);

    void bookTicket(int row, int seat, std::string note);

    void unbookTicket(int row, int seat);

    void buyTicket(int row, int seat);

    int getBoughtTicketsCount() const;

    bool operator <(const Event& other) const;

    const Date &getDate() const;

    void setDate(const Date &date);

};


#endif //TICKETS_EVENT_H

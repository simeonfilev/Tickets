//
// Created by Moni on 04-May-20.
//

#include "../headers/Event.h"

const std::string &Event::getName() const {
    return name;
}

void Event::setName(const std::string &name) {
    Event::name = name;
}


const Hall Event::getHall() const {
    return this->hall;
}

void Event::setHall(const Hall hall) {
    Event::hall = hall;
}

Event::Event() {
    int seatsCount = (this->getHall().getSeats() * this->getHall().getRows());
    for (int i = 0; i < seatsCount; i++) {
        this->seats.push_back(-1);
    }

}

Event::Event(const std::string &name, const Hall &hall, const Date &date) {
    int seatsCount = ((hall.getRows()) * (hall.getSeats()));
    for (int i = 0; i < seatsCount; i++) {
        this->seats.push_back(-1);
    }
    this->setName(name);
    this->setHall(hall);
    this->setDate(date);
}

int Event::getDay() const {
    return this->date.getDay();
}

int Event::getMonth() const {
    return this->date.getMonth();
}


int Event::getYear() const {
    return this->date.getYear();
}

const std::vector<int> &Event::getSeats() const {
    return seats;
}

//! books a ticket on given row and seat and if adds a note if exist
void Event::bookTicket(int row, int seat, const std::string &note) {
    Hall h = this->getHall();
    int seatToBook = ((row - 1) * h.getSeats()) + (seat - 1);
    this->seats[seatToBook] = 0;
    this->notes.insert(std::pair<std::pair<int, int>, std::string>(std::make_pair(row, seat), note));
}

//! unbooks a note on given row and seat
void Event::unbookTicket(int row, int seat) {

    Hall h = this->getHall();
    int seatToUnBook = ((row - 1) * h.getSeats()) + (seat - 1);
    this->seats[seatToUnBook] = -1;
    this->notes.erase(std::make_pair(row, seat));  //delete old note
}

//! buys a ticket on given row and seat
void Event::buyTicket(int row, int seat) {
    Hall h = this->getHall();
    int seatToUnBook = ((row - 1) * h.getSeats()) + (seat - 1);
    this->seats[seatToUnBook] = 1;
}

//! return the number of tickets bought
int Event::getBoughtTicketsCount() const {
    int counter = 0;
    for (int i = 0; i < this->getSeats().size(); i++) {
        if (this->getSeats()[i] == 1) {
            counter++;
        }
    }
    return counter;
}

bool Event::operator<(const Event &other) const {
    return getBoughtTicketsCount() > other.getBoughtTicketsCount();
}

const Date &Event::getDate() const {
    return date;
}

void Event::setDate(const Date &date) {
    Event::date = date;
}


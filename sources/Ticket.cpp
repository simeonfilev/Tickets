//
// Created by Moni on 06-May-20.
//

#include <iostream>
#include "../headers/Ticket.h"


const std::string &Ticket::getName() const {
    return name;
}

void Ticket::setName(const std::string &name) {
    Ticket::name = name;
}

int Ticket::getRow() const {
    return row;
}

void Ticket::setRow(int row) {
    Ticket::row = row;
}

int Ticket::getSeat() const {
    return seat;
}

void Ticket::setSeat(int seat) {
    Ticket::seat = seat;
}

int Ticket::getYear() const {
    return this->date.getYear();
}

int Ticket::getMonth() const {
    return this->date.getMonth();
}

int Ticket::getDay() const {
    return this->date.getDay();
}

Ticket::Ticket() {

}

Ticket::Ticket(const std::string &name, int row, int seat, const Date &date, const std::string &note) {
    this->setName(name);
    this->setNote(note);
    this->setRow(row);
    this->setDate(date);
    this->setSeat(seat);
    this->setBought(false);
    // 4 random numbers + row + 2 random numbers + seat + 4 random
    std::string hash = "";
    for (int i = 0; i < 4; i++) {
        int randomNumber = rand() % 10;

        hash += std::to_string(randomNumber);
    }
    hash += std::to_string(row);

    for (int i = 0; i < 2; i++) {
        int randomNumber = rand() % 10;
        hash += std::to_string(randomNumber);
    }
    hash += std::to_string(seat);
    for (int i = 0; i < 4; i++) {
        int randomNumber = rand() % 10;
        hash += std::to_string(randomNumber);
    }

    this->setHashedId(hash);
}


Ticket::Ticket(const std::string &name, int row, int seat, const Date &date, const std::string &note,
               const std::string &hall) {
    this->setHall(hall);
    Ticket(name, row, seat, date, note);
}

const std::string &Ticket::getHashedId() const {
    return this->hashedId;
}

void Ticket::setHashedId(const std::string &hashedId) {
    Ticket::hashedId = hashedId;
}

bool Ticket::isBought() const {
    return bought;
}

void Ticket::setBought(bool bought) {
    Ticket::bought = bought;
}

std::string Ticket::getId() const {
    return this->hashedId;
}

void Ticket::setId(const std::string &id) {
    this->hashedId = id;
}

const std::string &Ticket::getNote() const {
    return note;
}

void Ticket::setNote(const std::string &note) {
    Ticket::note = note;
}

const std::string &Ticket::getHall() const {
    return hall;
}

void Ticket::setHall(const std::string &hall) {
    Ticket::hall = hall;
}

const Date &Ticket::getDate() const {
    return date;
}

void Ticket::setDate(const Date &date) {
    Ticket::date = date;
}



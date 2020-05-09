//
// Created by Moni on 04-May-20.
//

#include "../headers/Hall.h"

int Hall::getId() const {
    return this->id;
}

void Hall::setId(int id) {
    Hall::id = id;
}

int Hall::getRows() const {
    return  this->rows;
}

void Hall::setRows(int rows) {
    Hall::rows = rows;
}

int Hall::getSeats() const {
    return this->seats;
}

void Hall::setSeats(int seats) {
    Hall::seats = seats;
}

Hall::Hall(int rows, int seats) {
    this->rows = rows;
    this->seats = seats;
}

Hall::Hall() {

}

bool Hall::operator==(const Hall &other) const {
    return this->seats == other.seats
           && this->rows == other.rows
           && this->id == other.id;
}

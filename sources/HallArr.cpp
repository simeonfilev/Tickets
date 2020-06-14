//
// Created by Moni on 06-May-20.
//

#include <stdexcept>
#include "../headers/HallArr.h"

HallArr::HallArr() {

}

void HallArr::copy(const HallArr &other) {
    for (int i = 0; i < other.getSize(); i++) {
        this->halls[i] = other.halls[i];
    }
}

int HallArr::getSize() const {
    return this->getHalls().size();
}

const std::vector<Hall> &HallArr::getHalls() const {
    return this->halls;
}

//! adds a hall in the hall array
HallArr &HallArr::addHall(Hall &newHall) {
    newHall.setId(this->getSize());
    this->halls.push_back(newHall);
    return *this;
}

//! returns a hall by given id
Hall *HallArr::getHallByID(int id) {
    for (int i = 0; i < this->getSize(); i++) {
        if (this->halls[i].getId() == id) {
            return &this->halls[i];
        }
    }
    throw std::invalid_argument("not found");

}


//
// Created by Moni on 06-May-20.
//

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

HallArr &HallArr::addHall( Hall &newHall) {
    newHall.setId(this->getSize());
    this->halls.push_back(newHall);
    return *this;
}

Hall *HallArr::getHallByID(int id) {
    for(int i=0;i<this->getSize();i++){
        if(this->halls[i].getId() == id){
            return &this->halls[i];
        }
    }
    return nullptr;
}


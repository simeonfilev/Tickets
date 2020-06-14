//
// Created by Moni on 06-May-20.
//

#ifndef TICKETS_HALLARR_H
#define TICKETS_HALLARR_H

#include <vector>
#include "Hall.h"

/*! \class HallArr
    \brief Клас който дефинира списък от зали
*/
class HallArr {
private:
    std::vector<Hall> halls;

    void copy(const HallArr &other);

public:
    HallArr();

    int getSize() const;

    const std::vector<Hall> &getHalls() const;

    HallArr &addHall(Hall &newHall);

    Hall *getHallByID(int id);
};


#endif //TICKETS_HALLARR_H

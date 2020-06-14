//
// Created by Moni on 04-May-20.
//

#ifndef TICKETS_HALL_H
#define TICKETS_HALL_H

#include <string>

/*! \class Hall
    \brief Клас който дефинира залата
*/
class Hall {
private:
    int id;
    int rows;
    int seats;
public:
    Hall();

    Hall(int rows, int seats);

    int getId() const;

    void setId(int id);

    int getRows() const;

    void setRows(int rows);

    int getSeats() const;

    void setSeats(int seats);

    bool operator==(const Hall &other) const;

};


#endif //TICKETS_HALL_H

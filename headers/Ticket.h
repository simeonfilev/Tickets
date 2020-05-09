//
// Created by Moni on 06-May-20.
//

#ifndef TICKETS_TICKET_H
#define TICKETS_TICKET_H


#include <string>
#include "Hall.h"
#include "Date.h"

class Ticket {
private:
    std::string hashedId;
    std::string name;
    std::string note;
    std::string hall;
    int row;
    int seat;
    Date date;
    bool bought;

public:
    Ticket();

    Ticket(std::string name,int row,int seat,Date date,std::string note,std::string hall);

    Ticket(std::string name,int row,int seat,Date date,std::string note);

    std::string getId() const;

    void setId(std::string id);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getRow() const;

    void setRow(int row);

    int getSeat() const;

    void setSeat(int seat);

    int getYear() const;

    void setYear(int year);

    int getMonth() const;

    void setMonth(int month);

    int getDay() const;

    void setDay(int day);

    const std::string &getHashedId() const;

    void setHashedId(const std::string &hashedId);

    std::string hashIt(int row,int seat, std::string name);

    bool isBought() const;

    void setBought(bool bought);

    const std::string &getNote() const;

    void setNote(const std::string &note);

    const std::string &getHall() const;

    void setHall(const std::string &hall);

    const Date &getDate() const;

    void setDate(const Date &date);
};


#endif //TICKETS_TICKET_H

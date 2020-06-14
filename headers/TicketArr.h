//
// Created by Moni on 06-May-20.
//

#ifndef TICKETS_TICKETARR_H
#define TICKETS_TICKETARR_H


#include <vector>
#include "Ticket.h"
#include "EventArr.h"
#include "HallArr.h"

/*! \class TicketArr
    \brief Клас който дефинира списък от билети
*/
class TicketArr {
private:
    std::vector<Ticket> tickets;

public:
    int getSize();

    const std::vector<Ticket> &getTickets() const;

    TicketArr &addTicket(const Ticket &newTicket);

    void removeTicketWithSeatNumberAndName(const std::string &name, int row, int seat, const Date &date);

    Ticket *getTicketWithID(const std::string &id);

    void addHashedId(const Ticket &ticket);


    void unbookTicket(const std::string &name, int row, int seat, const Date &date);

    void buyTicket(const std::string &name, int row, int seat, const Date &date);

    void
    printHallTickets(const Date &startDate, const Date &endDate,
                     Hall *hall, EventArr *eventArr);

    void
    printHallTickets(const Date &startDate, const Date &endDate, EventArr *eventArr);

    void getBookedTicketsWithHallName(const Date &date, Hall *hall, HallArr *halls);
};


#endif //TICKETS_TICKETARR_H

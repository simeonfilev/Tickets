//
// Created by Moni on 06-May-20.
//

#ifndef TICKETS_TICKETARR_H
#define TICKETS_TICKETARR_H


#include <vector>
#include "Ticket.h"
#include "EventArr.h"
#include "HallArr.h"

class TicketArr {
private:
    std::vector<Ticket> tickets;

public:
    int getSize();

    const std::vector<Ticket> &getTickets() const;

    TicketArr &addTicket(const Ticket &newTicket);

    void removeTicketWithSeatNumberAndName(std::string name,int row,int seat, Date date);

    Ticket *getTicketWithID(std::string id);

    void addHashedId(const Ticket &ticket);


    void unbookTicket(std::string name, int row, int seat, Date date);

    void buyTicket(std::string name, int row, int seat,Date date);

    void
    printHallTickets(Date startDate, Date endDate,
                     Hall* hall,EventArr *eventArr);
    void
    printHallTickets(Date startDate, Date endDate,EventArr *eventArr);

    void getBookedTicketsWithHallName(Date date, Hall *hall, HallArr * halls);
};


#endif //TICKETS_TICKETARR_H

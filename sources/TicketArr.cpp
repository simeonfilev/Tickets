//
// Created by Moni on 06-May-20.
//

#include "../headers/TicketArr.h"


const std::vector<Ticket> &TicketArr::getTickets() const {
    return tickets;
}

int TicketArr::getSize() {
    return this->getTickets().size();
}

TicketArr &TicketArr::addTicket(const Ticket &newTicket) {
    this->tickets.push_back(newTicket);
    return *this;
}

void TicketArr::addHashedId(const Ticket &ticket) {

}

Ticket *TicketArr::getTicketWithID(std::string id) {
    for(int i=0;i<this->getSize();i++){
        Ticket t = this->tickets[i];
        if(t.getId() == id){
            return &this->tickets[i];
        }
    }
    return nullptr;
}



void TicketArr::removeTicketWithSeatNumberAndName(std::string name, int row,int seat,Date date) {
    for(int i=0;i< this->getSize();i++){
        Ticket t = this->getTickets()[i];
        if(t.getName() == name
        && t.getDate() == date
        && t.getSeat() == seat
        && t.getRow() == row){
            this->tickets.erase(this->tickets.begin()+i);
            return;
        }
    }
}

void TicketArr::unbookTicket(std::string name, int row, int seat, Date date) {
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
    hash += std::to_string(seat + 1);
    for (int i = 0; i < 4; i++) {
        int randomNumber = rand() % 10;
        hash += std::to_string(randomNumber);
    }
    removeTicketWithSeatNumberAndName(name,row,seat,date);
}

void TicketArr::buyTicket(std::string name, int row, int seat, Date date) {
    for(int i=0;i< this->getSize();i++){
        Ticket t = this->getTickets()[i];
        if(t.getName() == name
            && t.getDate() == date
           && t.getSeat() == seat
           && t.getRow() == row){
            Ticket *ticketToChange = getTicketWithID(t.getId());
            ticketToChange->setBought(true);
            return;
        }
    }
}

void TicketArr::printHallTickets(Date startDate, Date endDate,Hall* hall,EventArr *eventArr) {
  long eventsTicketsSum =0;

   for(int i=0;i<eventArr->getSize();i++){
       Event event = eventArr->getEvents()[i];

       if(event.getDate()<=endDate && startDate<=event.getDate() && event.getHall().getId() == hall->getId()){
           std::cout<<"Event: "+event.getName()<<", Tickets bought: "<< event.getBoughtTicketsCount()<<std::endl;
           eventsTicketsSum += event.getBoughtTicketsCount();
       }
    }
    std::cout<<"Total tickets: "<<eventsTicketsSum<<std::endl;

}

void TicketArr::printHallTickets(Date startDate, Date endDate,EventArr *eventArr) {
    long eventsTicketsSum =0;

    for(int i=0;i<eventArr->getSize();i++){
        Event event = eventArr->getEvents()[i];
        if(event.getDate()<=endDate && startDate<=event.getDate()){
            std::cout<<"Event: "+event.getName()<<", Tickets bought: "<< event.getBoughtTicketsCount()<<std::endl;
            eventsTicketsSum += event.getBoughtTicketsCount();
        }
    }
    std::cout<<"Total tickets: "<<eventsTicketsSum<<std::endl;

}





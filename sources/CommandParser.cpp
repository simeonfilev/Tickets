//
// Created by Moni on 04-May-20.
//

#include <string>
#include <iostream>
#include "../headers/EventArr.h"
#include "../headers/HallArr.h"
#include "../headers/TicketArr.h"

enum Command {
    addevent,
    freeseats,
    book,
    unbook,
    buy,
    bookings,
    check,
    report,
    open,
    close,
    save,
    save_as,
    help,
    exit_command,
    most_popular
};

class CommandParser{
public:
    static Command getCommand(std::string const& str){
        if(str=="addevent")
            return addevent;
        if(str=="freeseats")
            return freeseats;
        if(str=="book")
            return book;
        if(str=="unbook")
            return unbook;
        if(str=="buy")
            return buy;
        if(str=="bookings")
            return bookings;
        if(str=="check")
            return check;
        if(str=="report")
            return report;
        if(str=="open")
            return open;
        if(str=="close")
            return close;
        if(str=="save")
            return save;
        if(str=="save as")
            return save_as;
        if(str=="help")
            return help;
        if(str=="exit")
            return exit_command;
        if(str=="popular")
            return most_popular;

    };
    void printHelpMsg(){
        std::cout<<"The following commands are supported:\n"
                   "open <file> opens <file>\n"
                   "close closes currently opened file\n"
                   "save saves the currently open file\n"
                   "saveas <file> saves the currently open file in <file>\n"
                   "help prints this information\n"
                   "exit exists the program"<<std::endl;
    }
    void printExitMsg(){
        std::cout<<"Exiting the program..."<<std::endl;
    }
    void addEvent(std::string expression,EventArr *events,HallArr* halls){
        //addevent <date> <hall> <name>
        std::string temp = expression;
        std::string date = temp.substr(0, temp.find(' '));//date
        temp = temp.substr(date.length()+1);
        std::string hallID = temp.substr(0, temp.find(' '));//id
        temp = temp.substr(hallID.length()+1);
        std::string name = temp.substr(0); // name

        Hall *hall = halls->getHallByID(std::stoi(hallID));
        if(hall == nullptr){
            return;
        }
        int day = std::stoi(date.substr(0,temp.find('-')));
        date = date.substr(std::to_string(day).length()+1);
        int month = std::stoi(date.substr(0,temp.find('-')));
        date = date.substr(std::to_string(month).length()+1);
        int year = std::stoi(date);

        try{
            Date *d = new Date(day,month,year);
            Event *e = new Event(name,*hall,*d);
            events->addEvent(*e);
        } catch (std::exception &e) {
            std::cout<<e.what()<<std::endl;
        }
    }

    void getFreeSeats(std::string expression, EventArr *eventArr) {
        // 23.03.2020 Chichovci
        std::string temp = expression;
        int day = std::stoi(temp.substr(0,temp.find('-')));
        temp = temp.substr(std::to_string(day).length()+1);
        int month = std::stoi(temp.substr(0,temp.find('-')));
        temp = temp.substr(std::to_string(month).length()+1);
        int year = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(year).length()+1);
        std::string name = temp;
        for(int i=0;i<eventArr->getSize();i++){
            Event e = eventArr->getEvents()[i];
            if(sameDate(day,month,year,e) && name==e.getName()){
                Hall hall = e.getHall();
                for(int z=1;z<=hall.getRows();z++){
                    for(int j=1;j<=hall.getSeats();j++){
                        int row = z;
                        int seat = j;
                        int seatToPrint = ((row -1) * hall.getSeats()) + (seat-1);
                        if(e.getSeats()[seatToPrint] == -1)
                            std::cout<<("["+std::to_string(z)+","+std::to_string(j)+"] ");
                        else
                            std::cout<<("[-,-] ");
                    }
                    //TODO FIX NEW LINE
                    std::cout<<"\n";
                }
            }
        }
    }

     bool sameDate(int day,int month,int year, Event &event){
        return event.getMonth() == month
               && event.getYear() == year
               && event.getDay() == day;
    }

    void bookTicket(std::string expression, EventArr *eventArr, TicketArr *ticketArr) {
        // book <row> <seat> <date> <name> <note>
        std::string temp = expression;

        int row = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(row).length()+1);

        int seat = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length()+1);

        std::string date = temp.substr(0,temp.find(' '));
        temp = temp.substr(date.length()+1);
        int day = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(day).length()+1);
        int month = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(month).length()+1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0,temp.find(' '));
        temp = temp.substr(name.length()+1);

        std::string note = temp.substr(0);

        try{
            Date *d = new Date(day,month,year);
            eventArr->getEventByNameAndDate(*d,name)->bookTicket(row,seat,note);
            ticketArr->addTicket(*new Ticket(name,row,seat,*d,note));
        } catch (std::exception &e) {
            std::cout<<e.what()<<std::endl;
        }



    }

    void unbookTicket(std::string expression, EventArr *eventArr, TicketArr *ticketArr) {
        // unbook <row> <seat> <date> <name>
        std::string temp = expression;

        int row = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(row).length()+1);

        int seat = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length()+1);

        std::string date = temp.substr(0,temp.find(' '));
        temp = temp.substr(date.length()+1);
        int day = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(day).length()+1);
        int month = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(month).length()+1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0);

        try{
            Date *d = new Date(day,month,year);
            eventArr->getEventByNameAndDate(*d,name)->unbookTicket(row,seat);
            ticketArr->unbookTicket(name,row,seat,*d);
        } catch (std::exception &e) {
            std::cout<<e.what()<<std::endl;
        }


    }

    void checkCode(std::string code) {
        if(code.length()!=12){
            std::cout<<"invalid code"<<std::endl;
            return;
        }
        // 4 random numbers + row + 2 random numbers + seat + 4 random = 12 cifri
        std::string rowStr = code.substr(4,1);
        int row = std::stoi(rowStr);
        std::string seatStr = code.substr(7,1);
        int seat = std::stoi(seatStr);
        std::cout<<"Row: "<<row<<" Seat: "<<seat<<std::endl;

    }

    void getBookings(std::string expression, EventArr *eventArr,TicketArr *ticketArr, HallArr *hallArr) {
        //check number of spaces
        std::string temp = expression;
        if(getNumberOfSpaces(expression)==1){ //two arguments
            std::string date = temp.substr(0,temp.find(' '));
            temp = temp.substr(date.length()+1);
            int day = std::stoi(date.substr(0,date.find('-')));
            date = date.substr(std::to_string(day).length()+1);
            int month = std::stoi(date.substr(0,date.find('-')));
            date = date.substr(std::to_string(month).length()+1);
            int year = std::stoi(date.substr(0));

            std::string name = temp.substr(0);

            try{
                Date *d = new Date(day,month,year);
                eventArr->getBookedTicketsOnDateWithName(*d,name);
            } catch (std::exception &e) {
                std::cout<<e.what()<<std::endl;
            }


        }
        else if(getNumberOfSpaces(expression)==0){
            std::string str = temp.substr(0);

            if(stringIsDate(str)){
                int day = std::stoi(str.substr(0,str.find('-')));
                str = str.substr(std::to_string(day).length()+1);
                int month = std::stoi(str.substr(0,str.find('-')));
                str = str.substr(std::to_string(month).length()+1);
                int year = std::stoi(str.substr(0));

                try{
                    Date *date = new Date(day,month,year);
                    eventArr->getBookedTicketsOnDate(*date);
                } catch (std::exception &e) {
                    std::cout<<e.what()<<std::endl;
                }
            }
            else{
                eventArr->getBookedTicketsOnName(str);
            }
        }
        else{
            std::cout<<"Invalid arguments"<<std::endl;
        }

    }
    bool stringIsDate(std::string str){
        for(int i=0;i<str.length();i++){
            if(str[i] != '-' && (!isdigit(str[i]))){
                return false;
            }
        }
        return true;
    }

    int getNumberOfSpaces(std::string expression){
        int counter =0;
        for(int i=0;i<expression.length();i++){
            if(expression[i] == ' ')
                counter++;
        }
        return counter;
    }

    void buyTicket(std::string expression, EventArr *eventArr,TicketArr *ticketArr) {
        std::string temp = expression;

        int row = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(row).length()+1);

        int seat = std::stoi(temp.substr(0,temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length()+1);

        std::string date = temp.substr(0,temp.find(' '));
        temp = temp.substr(date.length()+1);
        int day = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(day).length()+1);
        int month = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(month).length()+1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0);

        try{
            Date *d = new Date(day,month,year);
            eventArr->getEventByNameAndDate(*d,name)->buyTicket(row,seat);
            ticketArr->buyTicket(name,row,seat,*d);
        } catch (std::exception &e) {
            std::cout<<e.what()<<std::endl;
        }



    }

    void reportTickets(std::string expression,  TicketArr *ticketArr, EventArr *eventArr, HallArr *hallArr) {
        std::string temp = expression;

        std::string date = temp.substr(0,temp.find(' '));
        temp = temp.substr(date.length()+1);
        int startDay = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(startDay).length()+1);
        int startMonth = std::stoi(date.substr(0,date.find('-')));
        date = date.substr(std::to_string(startMonth).length()+1);
        int startYear = std::stoi(date.substr(0));

        std::string endDate = "";
        //check if have more than 2 arguments
        if(getNumberOfSpaces(expression) == 1){
            endDate=temp.substr(0);
        }
        else{
            endDate = temp.substr(0,temp.find(' '));
        }
        if(getNumberOfSpaces(expression)>1){
            temp =  temp.substr(endDate.length()+1);
        }
        int endDay = std::stoi(endDate.substr(0,date.find('-')));
        endDate = endDate.substr(std::to_string(endDay).length()+1);
        int endMonth = std::stoi(endDate.substr(0,date.find('-')));
        endDate = endDate.substr(std::to_string(endMonth).length()+1);
        int endYear = std::stoi(endDate.substr(0));

        if(getNumberOfSpaces(expression)>1){
            std::string hall = temp;
            int id = std::stoi(hall);

            try{
                Date *startDateObj = new Date(startDay,startMonth,startYear);
                Date *endDateObj = new Date(endDay,endMonth,endYear);
                Hall *h = hallArr->getHallByID( id);
                ticketArr->printHallTickets(*startDateObj,*endDateObj,h,eventArr);
            } catch (std::exception &e) {
                std::cout<<e.what()<<std::endl;
            }
        }else{
            try{
                Date *startDateObj = new Date(startDay,startMonth,startYear);
                Date *endDateObj = new Date(endDay,endMonth,endYear);
                ticketArr->printHallTickets(*startDateObj,*endDateObj,eventArr);
            } catch (std::exception &e) {
                std::cout<<e.what()<<std::endl;
            }
        }
    }

    void getMostPopular(EventArr *eventArr) {
        eventArr->printMostPopularEvents();
    }
};




//
// Created by Moni on 04-May-20.
//

#include <string>
#include <iostream>
#include <fstream>
#include "../headers/EventArr.h"
#include "../headers/HallArr.h"
#include "../headers/TicketArr.h"



//! An enum.
/*! More detailed enum description. */
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
    most_popular,
    invalid
};

/*! \class CommandParser
    \brief Служи за парсване на командите от main класа
*/
class CommandParser {
public:
    //! Retuns enum value(Command) based on string
    static Command getCommand(std::string const &str) {
        if (str == "addevent")
            return addevent;
        else if (str == "freeseats")
            return freeseats;
        else if (str == "book")
            return book;
        else if (str == "unbook")
            return unbook;
        else if (str == "buy")
            return buy;
        else if (str == "bookings")
            return bookings;
        else if (str == "check")
            return check;
        else if (str == "report")
            return report;
        else if (str == "open")
            return open;
        else if (str == "close")
            return close;
        else if (str == "save")
            return save;
        else if (str == "saveas")
            return save_as;
        else if (str == "help")
            return help;
        else if (str == "exit")
            return exit_command;
        else if (str == "popular")
            return most_popular;
        else
            return invalid;

    };

    //! Print hello msg
    void printHelpMsg() {
        std::cout << "The following commands are supported:\n"
                     "open <file> opens <file>\n"
                     "close closes currently opened file\n"
                     "save saves the currently open file\n"
                     "saveas <file> saves the currently open file in <file>\n"
                     "help prints this information\n"
                     "exit exists the program" << std::endl;
    }

    //! Print exit msg
    void printExitMsg() {
        std::cout << "Exiting the program..." << std::endl;
    }

    //! Add "addevent <date> <hall> <name>"
    void addEvent(std::string expression, EventArr *events, HallArr *halls) {
        //addevent <date> <hall> <name>
        std::string temp = expression;
        std::string date = temp.substr(0, temp.find(' '));//date
        temp = temp.substr(date.length() + 1);
        std::string hallID = temp.substr(0, temp.find(' '));//id
        temp = temp.substr(hallID.length() + 1);
        std::string name = temp.substr(0); // name

        try {
            Hall *hall = halls->getHallByID(std::stoi(hallID));
            int day = std::stoi(date.substr(0, temp.find('-')));
            date = date.substr(std::to_string(day).length() + 1);
            int month = std::stoi(date.substr(0, temp.find('-')));
            date = date.substr(std::to_string(month).length() + 1);
            int year = std::stoi(date);
            Date *d = new Date(day, month, year);
            Event *e = new Event(name, *hall, *d);
            events->addEvent(*e);
            std::cout << "Succesfully added event: " << name << std::endl;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }


    }

    //! Returns free seats
    void getFreeSeats(std::string expression, EventArr *eventArr) {
        // 23.03.2020 Chichovci
        std::string temp = expression;
        int day = std::stoi(temp.substr(0, temp.find('-')));
        temp = temp.substr(std::to_string(day).length() + 1);
        int month = std::stoi(temp.substr(0, temp.find('-')));
        temp = temp.substr(std::to_string(month).length() + 1);
        int year = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(year).length() + 1);
        std::string name = temp;
        for (int i = 0; i < eventArr->getSize(); i++) {
            Event e = eventArr->getEvents()[i];
            if (sameDate(day, month, year, e) && name == e.getName()) {
                Hall hall = e.getHall();
                for (int z = 1; z <= hall.getRows(); z++) {
                    for (int j = 1; j <= hall.getSeats(); j++) {
                        int row = z;
                        int seat = j;
                        int seatToPrint = ((row - 1) * hall.getSeats()) + (seat - 1);
                        if (e.getSeats()[seatToPrint] == -1)
                            std::cout << ("[" + std::to_string(z) + "," + std::to_string(j) + "] ");
                        else
                            std::cout << ("[-,-] ");
                    }
                    std::cout << "\n";
                }
            }
        }
    }

    //! Method for checking if two dates are the same
    bool sameDate(int day, int month, int year, Event &event) {
        return event.getMonth() == month
               && event.getYear() == year
               && event.getDay() == day;
    }

    //! Books a ticket "book <row> <seat> <date> <name> <note>"
    void bookTicket(std::string expression, EventArr *eventArr, TicketArr *ticketArr) {

        std::string temp = expression;

        int row = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(row).length() + 1);

        int seat = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length() + 1);

        std::string date = temp.substr(0, temp.find(' '));
        temp = temp.substr(date.length() + 1);
        int day = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(day).length() + 1);
        int month = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(month).length() + 1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0, temp.find(' '));
        temp = temp.substr(name.length() + 1);

        std::string note = temp.substr(0);

        try {
            Date *d = new Date(day, month, year);
            eventArr->getEventByNameAndDate(*d, name)->bookTicket(row, seat, note);
            ticketArr->addTicket(*new Ticket(name, row, seat, *d, note));
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }


    }

    //! Unbooks a ticket "unbook <row> <seat> <date> <name>"
    void unbookTicket(std::string expression, EventArr *eventArr, TicketArr *ticketArr) {

        std::string temp = expression;

        int row = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(row).length() + 1);

        int seat = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length() + 1);

        std::string date = temp.substr(0, temp.find(' '));
        temp = temp.substr(date.length() + 1);
        int day = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(day).length() + 1);
        int month = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(month).length() + 1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0);

        try {
            Date *d = new Date(day, month, year);
            eventArr->getEventByNameAndDate(*d, name)->unbookTicket(row, seat);
            ticketArr->unbookTicket(name, row, seat, *d);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }


    }

    //! Checks if a given code is in a valid format
    void checkCode(std::string code) {
        if (code.length() != 12) {
            std::cout << "invalid code" << std::endl;
            return;
        }
        // 4 random numbers + row + 2 random numbers + seat + 4 random = 12 cifri
        std::string rowStr = code.substr(4, 1);
        int row = std::stoi(rowStr);
        std::string seatStr = code.substr(7, 1);
        int seat = std::stoi(seatStr);
        std::cout << "Row: " << row << " Seat: " << seat << std::endl;

    }

    //! Prints all the bookings "bookings <date> <name>"
    void getBookings(std::string expression, EventArr *eventArr, TicketArr *ticketArr, HallArr *hallArr) {
        //check number of spaces
        std::string temp = expression;
        if (getNumberOfSpaces(expression) == 1) { //two arguments
            std::string date = temp.substr(0, temp.find(' '));
            temp = temp.substr(date.length() + 1);
            int day = std::stoi(date.substr(0, date.find('-')));
            date = date.substr(std::to_string(day).length() + 1);
            int month = std::stoi(date.substr(0, date.find('-')));
            date = date.substr(std::to_string(month).length() + 1);
            int year = std::stoi(date.substr(0));

            std::string name = temp.substr(0);

            try {
                Date *d = new Date(day, month, year);
                eventArr->getBookedTicketsOnDateWithName(*d, name);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }


        } else if (getNumberOfSpaces(expression) == 0) {
            std::string str = temp.substr(0);

            if (stringIsDate(str)) {
                int day = std::stoi(str.substr(0, str.find('-')));
                str = str.substr(std::to_string(day).length() + 1);
                int month = std::stoi(str.substr(0, str.find('-')));
                str = str.substr(std::to_string(month).length() + 1);
                int year = std::stoi(str.substr(0));

                try {
                    Date *date = new Date(day, month, year);
                    eventArr->getBookedTicketsOnDate(*date);
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            } else {
                eventArr->getBookedTicketsOnName(str);
            }
        } else {
            std::cout << "Invalid arguments" << std::endl;
        }

    }

    //! Checks if given string is a date
    bool stringIsDate(std::string str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != '-' && (!isdigit(str[i]))) {
                return false;
            }
        }
        return true;
    }

    //! Returns the number of spaces
    int getNumberOfSpaces(const std::string &expression) {
        int counter = 0;
        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] == ' ')
                counter++;
        }
        return counter;
    }

    //! Buys a ticket
    void buyTicket(std::string expression, EventArr *eventArr, TicketArr *ticketArr) {
        std::string temp = expression;

        int row = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(row).length() + 1);

        int seat = std::stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(std::to_string(seat).length() + 1);

        std::string date = temp.substr(0, temp.find(' '));
        temp = temp.substr(date.length() + 1);
        int day = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(day).length() + 1);
        int month = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(month).length() + 1);
        int year = std::stoi(date.substr(0));

        std::string name = temp.substr(0);

        try {
            Date *d = new Date(day, month, year);
            eventArr->getEventByNameAndDate(*d, name)->buyTicket(row, seat);
            ticketArr->buyTicket(name, row, seat, *d);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }


    }

    //! Prints a report given two ranges
    void reportTickets(std::string expression, TicketArr *ticketArr, EventArr *eventArr, HallArr *hallArr) {
        std::string temp = expression;

        std::string date = temp.substr(0, temp.find(' '));
        temp = temp.substr(date.length() + 1);
        int startDay = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(startDay).length() + 1);
        int startMonth = std::stoi(date.substr(0, date.find('-')));
        date = date.substr(std::to_string(startMonth).length() + 1);
        int startYear = std::stoi(date.substr(0));

        std::string endDate = "";
        //check if have more than 2 arguments
        if (getNumberOfSpaces(expression) == 1) {
            endDate = temp.substr(0);
        } else {
            endDate = temp.substr(0, temp.find(' '));
        }
        if (getNumberOfSpaces(expression) > 1) {
            temp = temp.substr(endDate.length() + 1);
        }
        int endDay = std::stoi(endDate.substr(0, date.find('-')));
        endDate = endDate.substr(std::to_string(endDay).length() + 1);
        int endMonth = std::stoi(endDate.substr(0, date.find('-')));
        endDate = endDate.substr(std::to_string(endMonth).length() + 1);
        int endYear = std::stoi(endDate.substr(0));

        if (getNumberOfSpaces(expression) > 1) {
            std::string hall = temp;
            int id = std::stoi(hall);

            try {
                Date *startDateObj = new Date(startDay, startMonth, startYear);
                Date *endDateObj = new Date(endDay, endMonth, endYear);
                Hall *h = hallArr->getHallByID(id);
                ticketArr->printHallTickets(*startDateObj, *endDateObj, h, eventArr);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        } else {
            try {
                Date *startDateObj = new Date(startDay, startMonth, startYear);
                Date *endDateObj = new Date(endDay, endMonth, endYear);
                ticketArr->printHallTickets(*startDateObj, *endDateObj, eventArr);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    //! Prints the most popular events
    void getMostPopular(EventArr *eventArr) {
        eventArr->printMostPopularEvents();
    }

    //! method for executing given commands
    void execute(std::string commandExpression, EventArr *events, HallArr *halls, TicketArr *tickets) {
        std::string command = commandExpression;
        command = command.substr(0, commandExpression.find(' '));
        Command cmd = CommandParser::getCommand(command);
        switch (cmd) {
            case addevent:
                //addevent <date> <hall> <name>
                // date - 23.2.2020
                // hall - id (3)
                // name - chichovci
                this->addEvent(commandExpression.substr(command.length() + 1), events, halls);
                break;
            case freeseats:
                // -1 Neprodadeni
                // 0 zapazeni
                // 1 prodadeni
                this->getFreeSeats(commandExpression.substr(command.length() + 1), events);
                break;
            case book:
                this->bookTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case unbook:
                this->unbookTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case buy:
                this->buyTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case bookings:
                this->getBookings(commandExpression.substr(command.length() + 1), events, tickets, halls);
                break;
            case check:
                this->checkCode(commandExpression.substr(command.length() + 1));
                break;
            case report:
                this->reportTickets(commandExpression.substr(command.length() + 1), tickets, events, halls);
                break;
            case most_popular:
                // popular
                this->getMostPopular(events);
                break;
            case invalid:
            default:
                std::cout << "invalid command" << std::endl;
        }
    }

    //! Saves the file
    void saveFile(std::string fileName, std::string currentInput) {
        std::ofstream outfile;
        outfile.open(encodePath(fileName), std::ios::app);
        outfile << std::endl;
        outfile << currentInput;
        outfile.close();
    }

    //! Encodes the path "./mm.txt" -> ".//m.txt"
    std::string encodePath(std::string path) {
        std::string ans = "";
        int indexOfExtension = path.rfind('.');
        for (int i = 0; i < path.size(); i++) {
            if (indexOfExtension != i && (path.at(i) == '.' || path.at(i) == '/')) {
                ans += path.at(i);
            }
            ans += path.at(i);
        }
        return ans;
    }

    //! Decodes the path ".//m.txt" -> "./m.txt"
    std::string decodePath(const std::string &path) {
        std::string ans = "";
        for (int i = 1; i < path.size(); i++) {
            if (path.at(i - 1) == path.at(i) && (path.at(i) == '.' || path.at(i) == '/')) {
                continue;
            }
            ans += path.at(i - 1);
        }
        ans += path.at(path.size() - 1);
        return ans;
    }

    //! Opens the file
    void openFile(const std::string &fileName, std::string currentInput, EventArr *events, HallArr *halls,
                  TicketArr *tickets) {
        std::ifstream myfile(encodePath(fileName));
        std::string line;
        if (!myfile) {
            std::ofstream outfile(encodePath(fileName));
            outfile.close();//create file if it doesn't exist
        } else if (myfile) {
            if (myfile.is_open()) {
                while (getline(myfile, line)) {
                    if (lineIsMoreThanWhiteSpaces(line)) {
                        line = removeNewLines(line);
                        execute(line, events, halls, tickets);
                        currentInput += line + "\n";
                    }
                }
                myfile.close();
            } else std::cout << "Unable to open file";
        }
        myfile.close();
    }

    //! removes all the new line at the end of string
    std::string removeNewLines(const std::string &line) {
        std::string formatted = line;
        while (formatted.find("\r") != std::string::npos) {
            formatted.erase(line.find("\r"), 2);
        }
        while (formatted.find("\n") != std::string::npos) {
            formatted.erase(line.find("\n"), 2);
        }
        return formatted;
    }

    //! Returns bool if line isn't only white spaces
    bool lineIsMoreThanWhiteSpaces(const std::string &line) {
        for (int i = 0; i < line.size(); i++) {
            if (line.at(i) != '\n' || line.at(i) != '\t' || line.at(i) != ' ') {
                return true;
            }
        }
        return false;
    }
};




#include <iostream>

#include "../headers/EventArr.h"
#include "CommandParser.cpp"

#include <fstream>

int main() {
    EventArr *events = new EventArr();
    HallArr *halls = new HallArr();
    TicketArr *tickets = new TicketArr();
    std::string path = "C:\\Users\\Moni\\CLionProjects\\Tickets\\project.txt";
    std::ofstream myfile(path);


    Hall *h = new Hall(5, 3);
    Hall *h1 = new Hall(5, 4);

    halls->addHall(*h);
    halls->addHall(*h1);

    //events->addEvent(*e1);
    std::string commandExpression;
    getline(std::cin, commandExpression);
    std::string currentInput = "";
    CommandParser *commandParser = new CommandParser();
    bool userWantsToQuit = false;
    while (!userWantsToQuit) {
        std::string command = commandExpression;
        command = command.substr(0, commandExpression.find(' '));
        Command cmd = CommandParser::getCommand(command);
        switch (cmd) {
            case addevent:
                //addevent <date> <hall> <name>
                // date - 23.2.2020
                // hall - id (3)
                // name - chichovci
                commandParser->addEvent(commandExpression.substr(command.length() + 1), events, halls);
                break;
            case freeseats:
                // -1 Neprodadeni
                // 0 zapazeni
                // 1 prodadeni
                commandParser->getFreeSeats(commandExpression.substr(command.length() + 1), events);
                break;
            case book:
                commandParser->bookTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case unbook:
                commandParser->unbookTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case buy:
                commandParser->buyTicket(commandExpression.substr(command.length() + 1), events, tickets);
                break;
            case bookings:
                commandParser->getBookings(commandExpression.substr(command.length() + 1), events, tickets, halls);
                break;
            case check:
                commandParser->checkCode(commandExpression.substr(command.length() + 1));
                break;
            case report:
                commandParser->reportTickets(commandExpression.substr(command.length() + 1), tickets, events, halls);
                break;
            case most_popular:
                // popular
                commandParser->getMostPopular(events);
                break;
            case open:
                // TODO
                break;
            case close:
                myfile.close();
                break;
            case save:
                myfile.flush();
                break;
            case save_as:
                //TODO  commandParser->saveToFileWithPath(commandExpression.substr(command.length()+1),myfile)
                break;
            case help:
                commandParser->printHelpMsg();
                break;
            case exit_command:
                commandParser->printExitMsg();
                userWantsToQuit = true;
                break;

            default:
                std::cout << "invalid command" << std::endl;
        }
        if (!userWantsToQuit) {
            if (cmd == CommandParser::getCommand("save")) {
                getline(std::cin, commandExpression);
                continue;
            }
            // TODO IF COMMAND IS INVALID CHECK
            myfile << commandExpression + "\n";
            currentInput += commandExpression + "\n";
            getline(std::cin, commandExpression);
        }
    }
    myfile.close();
    // output<<currentInput<<std::endl;
    return 0;
}

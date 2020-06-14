#include <iostream>

#include "../headers/EventArr.h"
#include "CommandParser.cpp"


/**********************************************************//**
 * @file    main.cpp
 * @author  Moni
 * @brief   Main function and support functions.
 * @details None
 */
int main() {
    EventArr *events = new EventArr();
    HallArr *halls = new HallArr();
    TicketArr *tickets = new TicketArr();
    CommandParser *commandParser = new CommandParser();
    std::string filename;
    bool userWantsToQuit = false;
    bool closed = false;
    std::string commandExpression;
    getline(std::cin, commandExpression);
    std::string currentInput = "";

    Hall *h = new Hall(5, 3);
    Hall *h1 = new Hall(5, 4);

    halls->addHall(*h);
    halls->addHall(*h1);

    while (!userWantsToQuit) {
        std::string command = commandExpression;

        command = command.substr(0, commandExpression.find(' '));

        Command cmd = CommandParser::getCommand(command);
        if (closed && (cmd != open)) {
            std::cout << "You can only use command: open" << std::endl;
            getline(std::cin, commandExpression);
        } else {
            switch (cmd) {
                case addevent:
                case freeseats:
                case book:
                case unbook:
                case buy:
                case bookings:
                case check:
                case report:
                case most_popular:
                    commandParser->execute(commandExpression, events, halls, tickets);
                    break;
                case open:
                    //open PATH
                    filename = commandExpression.substr(commandExpression.find(' ') + 1);
                    commandParser->openFile(filename, currentInput, events, halls, tickets);
                    closed = false;
                    break;
                case close:
                    events = new EventArr();
                    halls = new HallArr();
                    tickets = new TicketArr();
                    closed = true;
                    break;
                case save:
                    commandParser->saveFile(filename, currentInput);
                    currentInput = "";
                    break;
                case save_as:
                    commandParser->saveFile(commandExpression.substr(command.length() + 1), currentInput);
                    break;
                case help:
                    commandParser->printHelpMsg();
                    break;
                case exit_command:
                    commandParser->printExitMsg();
                    userWantsToQuit = true;
                    break;
                case invalid:
                default:
                    std::cout << "Invalid command" << std::endl;
                    break;
            }
            if (!userWantsToQuit) {
                // check if command is valid
                if (cmd != open && cmd != help && cmd != save && cmd != save_as && cmd != invalid)
                    currentInput += commandExpression + "\n";
                getline(std::cin, commandExpression);
            }
        }
    }
    return 0;
}

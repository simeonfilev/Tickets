cmake_minimum_required(VERSION 3.16)
project(Tickets)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tickets sources/main.cpp sources/Hall.cpp headers/Hall.h sources/CommandParser.cpp sources/Event.cpp headers/Event.h sources/EventArr.cpp headers/EventArr.h sources/HallArr.cpp headers/HallArr.h sources/Ticket.cpp headers/Ticket.h sources/TicketArr.cpp headers/TicketArr.h sources/Date.cpp headers/Date.h)
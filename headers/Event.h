//
// Created by Moni on 04-May-20.
//
#include <iostream>
#include <vector>
#include "Hall.h"
#include "map"
#include "Date.h"

#ifndef TICKETS_EVENT_H
#define TICKETS_EVENT_H


/*! \class Event
    \brief Клас който дефинира събитие
*/
class Event {
private:
    std::string name; /*!< пази името на събитието */
    Date date; /*!< пази датата на събитието */
    Hall hall; /*!< пази залата на събитието */
    std::vector<int> seats;  /*!< пази местата на събитието */
    std::map<std::pair<int, int>, std::string> notes;  /*!< пази бележките на събитието */
public:
    Event();  /*!< базов конструктор */

    Event(const std::string &name, const Hall &hall, const Date &date);/*!< конструктор с аргументи */

    const std::string &getName() const; /*!< геттър на името */

    void setName(const std::string &name); /*!< сетър на името */

    int getDay() const; /*!< връща  деня на събитието */

    int getMonth() const;  /*!< връща месеца на събитието */

    int getYear() const;  /*!< връща годината на събитието */

    const std::vector<int> &getSeats() const;  /*!< връща местата на събитието */

    const Hall getHall() const;  /*!< връща залата на събитието */

    void setHall(Hall hall);  /*!< сетър на залата */

    void bookTicket(int row, int seat, const std::string &note);  /*!< метод за запазване на билет */

    void unbookTicket(int row, int seat);  /*!< метод за премахване на запазен билет */

    void buyTicket(int row, int seat);  /*!< метод за закупуване на билет */

    int getBoughtTicketsCount() const;  /*!< метод който връща броя на закупените билети */

    bool operator<(const Event &other) const;

    const Date &getDate() const;  /*!< геттър на датата */

    void setDate(const Date &date);  /*!< сетър на датата */

};


#endif //TICKETS_EVENT_H

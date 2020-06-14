//
// Created by Moni on 09-May-20.
//

#ifndef TICKETS_DATE_H
#define TICKETS_DATE_H


/*! \class Date
    \brief Клас който дефинира датата
*/
class Date {
private:
    int day, month, year;

public:
    Date();

    Date(int day, int month, int year);

    int getDay() const;

    void setDay(int day);

    int getMonth() const;

    void setMonth(int month);

    int getYear() const;

    void setYear(int year);

    bool operator<(const Date &other) const;

    bool operator<=(const Date &other) const;

    bool operator==(const Date &other) const;

    bool isLeapYear() const;
};


#endif //TICKETS_DATE_H

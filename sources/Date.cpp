//
// Created by Moni on 09-May-20.
//

#include <stdexcept>
#include "../headers/Date.h"
static int monthsLenght[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(int day, int month, int year) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

int Date::getDay() const {
    return day;
}

void Date::setDay(int day) {
    if(this->getMonth() == 2){
        if(day == 29 && isLeapYear()){
            this->day = day;
        }
        else if(day == 29){
            throw std::invalid_argument( "invalid day" );
        }
        else if(day>=1 && day<29){
            this->day = day;
        }
    }
    else if(this->getMonth()>=1 && this->getMonth()<=12){
        int monthDays = monthsLenght[this->getMonth()];
        if(day >= 1 && day<=monthDays){
            this->day = day;
        }
        else{
            throw std::invalid_argument( "invalid day" );
        }
    }
    else{
        throw std::invalid_argument( "invalid day" );
    }
}

int Date::getMonth() const {
    return month;
}

void Date::setMonth(int month) {
    if(month>=1 && month<=12){
        Date::month = month;
    }
    else{
    throw std::invalid_argument( "invalid month" );
    }
}

int Date::getYear() const {
    return year;
}

void Date::setYear(int year) {
    Date::year = year;
}

bool Date::operator<(const Date &other) const {
    if(this->getYear() < other.getYear()){
        return true;
    }
    else if(this->getYear() == other.getYear()){
        if(this->getMonth()< other.getMonth()){
            return true;
        }
        else if(this->getMonth() == other.getMonth()){
            return this->getDay() < other.getDay();
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Date::operator<=(const Date &other) const {
    if(this->getYear() < other.getYear()){
        return true;
    }
    else if(this->getYear() == other.getYear()){
        if(this->getMonth()< other.getMonth()){
            return true;
        }
        else if(this->getMonth() == other.getMonth()){
            if(this->getDay() == other.getDay()){
                return true;
            }
            return this->getDay() <= other.getDay();
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Date::isLeapYear() const {
    if (this->getYear() % 4 == 0)
    {
        if (this->getYear() % 100 == 0)
        {
            return this->getYear() % 400 == 0;
        }
        else
            return true;
    }
    else
        return false;
}

Date::Date() {

}

bool Date::operator==(const Date &other) const {
    return this->getYear() == other.getYear()
           && this->getMonth() == other.getMonth()
           && this->getDay() == other.getDay();
}



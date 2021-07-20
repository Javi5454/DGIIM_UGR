/**
 * @file DateTime.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <iostream>
#include <sstream>
#include "DateTime.h"
#include <algorithm> 
using namespace std;

/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split(const std::string &line, int &y, int  &m, int &d, int  &h, int &mn, int &s);
/**
 * @brief auxiliary function to check if a string only contais numbers
 * @param string to check
 * @return true if only contains numbers, false if not
 */

DateTime::DateTime() {
    initDefault();
}

void DateTime::initDefault() {
    set(DATETIME_DEFAULT);
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {
    
    int nDays;
    bool bisiesto = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    
    if((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8)
            || (month == 10) || (month == 12)){
            
        nDays = 31;
    }
    else if (month == 2)
    {
        if(bisiesto)
        {
            nDays = 29;
        }
        else
        {
            nDays = 28;
        }
    }
    else
    {
        nDays = 30;
    }
    
    
    return ((month <= 12) && (month >= 1) && (day <= nDays) && (day >= 0) && (hour <=23)
            && (hour >= 0) && (min >= 0) && (min <= 59) && (sec <= 59) && (sec >= 0)); 

}

void split(const std::string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s) {
    
    string add;
    
    if(line.length() == 23){
        y = stoi(line.substr(0,4));
        m = stoi(line.substr(5,2));
        d = stoi(line.substr(8,2));
        
        h = stoi(line.substr(11,2));
        mn = stoi(line.substr(14,2));
        s = stoi(line.substr(17,2));
    }
    else
    {
        m = 15; //Le pasamos un valor incorrecto del mes
    }
     
}

void DateTime::set(const std::string  &line) {
    
    int y, m, d, h, mn, s;
    
    split(line, y, m, d, h, mn, s);
    
    if(isCorrect(y, m, d, h, mn, s))
    {
        _year = y;
        _month = m;
        _day = d;
        _hour = h;
        _min = mn;
        _sec = s;
    }
    else
    {
        initDefault();
    }
}

DateTime::DateTime(const string  &line) {
    
    int y, m, d, h, mn, s;
    
    split(line, y, m, d, h, mn, s);
    
    if(isCorrect(y, m, d, h, mn, s))
    {
        set(line);
    }
    else
    {
        initDefault();
    }
    
}

int DateTime::year() const {
    
    return _year;
}

int DateTime::month() const {
    
    return _month;
}

int DateTime::day() const {
    
    return _day;
}

int DateTime::hour() const {
    
    return _hour;
}

int DateTime::min() const {
    
    return _min;
}

int DateTime::sec() const {
    
    return _sec;
}

bool DateTime::isBefore(const DateTime  &one)  const {
    
    bool resultado;
    
    if(_year > one.year())
    {
        resultado = false;
    }
    else if(_year < one.year())
    {
        resultado = true;
    }
    else
    {
        if(_month > one.month())
        {
            resultado = false;
        }
        else if(_month < one.month())
        {
            resultado = true;
        }
        else
        {
            if(_day > one.day())
            {
                resultado = false;
            }
            else if (_day < one.day())
            {
                resultado = true;
            }
            else
            {
                if(_hour > one.hour())
                {
                    resultado = false;
                }
                else if (_hour < one.hour())
                {
                    resultado = true;
                }
                else
                {
                    if(_min > one.min())
                    {
                        resultado = false;
                    }
                    else if (_min < one.min())
                    {
                        resultado = true;
                    }
                    else
                    {
                        if(_sec >= one.sec())
                        {
                            resultado = false;
                        }
                        else 
                        {
                            resultado = true;
                        }
                    }
                }
            }
        }
    }
    
    return resultado;
}


int DateTime::weekDay() const  {
    
    int a, y, m ,d;
    
    a = (14 - month()) / 12;
    y = year() - a;
    m = month() + (12*a) - 2;
    d = (day() + y + (y/4) - (y/100) + (y/400) + (31*m)/12) % 7;
    
    return d;
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}


bool DateTime::sameDay(const DateTime &other) const {  
    if((_year == other.year()) && (_month == other.month()) && (_day == other.day())){
        return true;
    }
    else{
        return false;
    }
}
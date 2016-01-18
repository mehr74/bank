#ifndef _DATE_H
#define _DATE_H

// Copyright @ Owen Astrachan

#include <iostream>
#include <string>
using namespace std;

enum DateType
{
    GREGORIAN,
    JALALI
};

enum GregorianMonthNamesEnum
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

enum jalaliMonthNamesEnum
{
    FARVARDIN = 1,
    ORDIBEHESHT,
    KHORDAD,
    TIR,
    MORDAD,
    SHAHRIVAR,
    MEHR,
    ABAN,
    AZAR,
    DEY,
    BAHMAN,
    ESFAND
};

class Date
{
  public:
    Date();                       // construct date with default value
    Date(int m,int d,int y, DateType = GREGORIAN);      // construct date with specified values

    int Month(DateType = GREGORIAN) const;     // return month corresponding to date
    int Day(DateType = GREGORIAN) const;     // return day corresponding to date
    int Year(DateType = GREGORIAN) const;     // return year corresponding to date
    int DaysIn(DateType = GREGORIAN) const;     // return # of days in month
    string DayName() const;     // "monday", "tuesday", ... or "sunday"
    string GregorianMonthName() const;     // "january","february",... or "december"
    string JalaliMonthName() const;
    long Absolute() const;     // number of days since 1 A.D. for date
    string GregorianToString()    const;     // returns string for date in ascii
    string JalaliToString()    const;

    bool Equal(const Date & rhs) const;  // for implementing <, >, etc
    bool Less(const Date & rhs) const;
    
    Date operator ++(int);         // add one day, postfix operator
    Date operator --(int);         // subtract one day, postfix operator
    Date& operator +=(long dx);    // add dx, e.g., jan 1 + 31 = feb 1
    Date& operator -=(long dx);    // subtract dx, e.g., jan 1 - 1 = dec 31


  private:

    Date(long days);          // construct date from absolute #

    // gregorian date
    int myGDay;                    // day of week, 0-6
    int myGMonth;                  // month, 0-11
    int myGYear;                   // year in four digits, e.g., 1899

    // jalali date
    int myJDay;
    int myJMonth;
    int myJYear;

    void CheckDate(int m, int d, int y, DateType t); // make sure that date is valid
    void GregorianToJalali();           // convert gregorian date to jalali date
    void JalaliToGregorian();
};

Date operator + (const Date & d, long dx);   // add dx to date d
Date operator + (long dx, const Date & d);   // add dx to date d
Date operator - (const Date & d, long dx);   // subtract dx from date d
long operator - (const Date & lhs, const Date & rhs);

ostream & operator << (ostream & os, const Date & d);
bool operator == (const Date & lhs, const Date & rhs);
bool operator != (const Date & lhs, const Date & rhs);
bool operator <  (const Date & lhs, const Date & rhs);
bool operator >  (const Date & lhs, const Date & rhs);
bool operator <= (const Date & lhs, const Date & rhs);
bool operator >= (const Date & lhs, const Date & rhs);

#endif

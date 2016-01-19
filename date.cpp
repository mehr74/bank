#include "date.h"
#include <time.h>
#include <stdio.h>   // for sprintf

static int DaysInMonth(int,int, DateType t = GREGORIAN);             // # of days in month in year
static bool IsLeap(int year, DateType t = GREGORIAN);                // is year a leap year

static string dayNames [] = {"Sunday",  "Monday", "Tuesday","Wednesday",
                      "Thursday","Friday", "Saturday"};

static string gregorianMonthNames [] = {"January","February","March","April",
                 "May","June","July","August",
                 "September","October","November","December"};

static string jalaliMonthNames [] = {"Farvardin","Ordibehesht","Khordad","Tir",
                 "Mordad","Shahrivar","Mehr","Aban",
                 "Azar","Dey","Bahman","Esfand"};

static int gDaysInMonth [] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int jDaysInMonth [] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

Date::Date()
{
    static struct tm timeHolder;
    static struct tm *date = &timeHolder;
    time_t tloc;
    
    time(&tloc);

    date = localtime(&tloc);
    
    myGMonth = date->tm_mon+1;
    myGDay   = date->tm_mday;
    myGYear  = date->tm_year+1900;             // struct tm based on 1900
    GregorianToJalali();
}

Date::Date(int d, int m, int y, DateType t)
{
    CheckDate(m,d,y,t);
}

Date::Date(long days)
{
    long prior = days - 1;                // prior days
    long years400 = prior / 146097L;      // # of 400 year cycles
    long days400 = prior % 146097L;       // days NOT in years400

    long years100 = days400 / 36524L;     // # 100 yr. cycles not checked
    long days100 =  days400 % 36524L;     // days NOT already included

    long years4 = days100 / 1461L;        // # 4 yr cycles not checked
    long days4 = days100 % 1461L;         // days NOT already included

    long year1 = days4 / 365L;            // # years not already checked
    long day1  = days4 % 365L;            // days NOT already included

    // use "magic formula" from SP&E article
    long finalDay;
    long finalYear = 400*years400 + 100*years100 + 4*years4 + year1;

    if (years100 == 4 || year1 == 4)
    {
        finalDay = 366;
    }
    else{
        finalDay = day1 + 1;
        finalYear += 1;
    }

    // now have year and day #, find month and day in month
    myGMonth = 1;
    while (myGMonth <= 12 && 0 < finalDay){
    finalDay -= DaysInMonth(myGMonth, int(finalYear));
    myGMonth += 1;
    }
    myGMonth -= 1;                              // went one to far
    finalDay += DaysInMonth(myGMonth, int(finalYear));

    myGDay = int(finalDay);
    myGYear = int(finalYear);
}


int Date::Month(DateType t) const
{
    if(t == GREGORIAN)
        return myGMonth;
    else
        return myJMonth;
}

int Date::Day(DateType t) const
{
    if(t == GREGORIAN)
        return myGDay;
    else
        return myJDay;
}

int Date::Year(DateType t) const
{
    if(t == GREGORIAN)
        return myGYear;
    else
        return myJYear;
}

string Date::GregorianToString() const
// postcondition: returns string (ascii) for date: day, month, year
{
    const int BUFSIZE = 50;
    char buf[BUFSIZE];
    sprintf(buf," %d %d",myGDay, myGYear);

    return GregorianMonthName() + buf;
}

string Date::JalaliToString() const
{
    const int BUFSIZE = 50;
    char buf[BUFSIZE];
    sprintf(buf," %d %d",myJDay, myJYear);

    return JalaliMonthName() + buf;
}


static bool IsLeap(int year, DateType t)
{
    if(t == GREGORIAN)
    {
        if (year % 400 == 0)
        {
            return true;
        }
        else if (year % 100 == 0)
        {
            return false;
        }
        else if (year % 4 == 0)
        {
            return true;
        }
        return false;
    }
    else
    {
        if(year % 4 == 3)
            return true;
        else
            return false;
    }
}

static int DaysInMonth(int month,int year, DateType t)
{
    int days;
    if(t == GREGORIAN)
    {
        days = gDaysInMonth[month];
        if(month == 2 && IsLeap(year))
        {
            days = 29;
        }
    }
    else
    {
        days = jDaysInMonth[month];
        if(month == 12 && IsLeap(year, JALALI))
        {
            days = 30;
        }
    }
    return days;
}


int Date::DaysIn(DateType t) const
{
    if(t == GREGORIAN)
    {
    return DaysInMonth(myGMonth,myGYear, GREGORIAN);
    }
    else
    {
        return DaysInMonth(myJMonth, myJYear, JALALI);
    }
}

long Date::Absolute() const
// postcondition: returns absolute # days corresponding to Date
//                assuming January 1, 1 B.C is day 1
{
    int m = 1;               // start in January;
    int daysBefore = 0;      // count # days before month

    while (m < myGMonth){       // tally # of days in preceding months
        daysBefore += DaysInMonth(m,myGYear, GREGORIAN);
        m += 1;
    }

    // days before this year
    long dayYears = 365 * ((long)(myGYear) - 1);

    // add 1 extra day for each leap year

    int leapYears = (myGYear - 1) / 4;     // initial # of leap years

    leapYears -= (myGYear - 1) / 100;      // subtract years divisible by 100
    leapYears += (myGYear - 1) / 400;      // add back years divisibly by 400

    return myGDay + daysBefore + dayYears + leapYears;
}

string Date::DayName() const
{
    return dayNames[int(Absolute() % 7)];
}

string Date::GregorianMonthName() const
{
    return gregorianMonthNames[myGMonth-1];
}

string Date::JalaliMonthName() const
{
    return jalaliMonthNames[myJMonth-1];
}

ostream & operator << (ostream & os, const Date & d)
{
    os << d.GregorianToString();
    return os;
}

Date& Date::operator +=(long dx)
{
    *this = Date(Absolute()+dx);
    return *this;
}

Date& Date::operator -=(long dx)
{
    *this = Date(Absolute()-dx);
    return *this;
}

Date Date::operator ++(int)
{
    Date hold = *this;
    *this += 1;
    return hold;
}

Date Date::operator --(int)
{
    Date hold = *this;
    *this -= 1;
    return hold;
}

Date operator + (const Date & d, long dx)
{
    return Date(d) += dx;
}

Date operator + (long dx, const Date & d)
{
    return d+dx;
}

Date operator - (const Date & d, long dx)
{
    return Date(d) -= dx;
}

long operator - (const Date & lhs, const Date & rhs)
{
    return lhs.Absolute() - rhs.Absolute();
}

void Date::GregorianToJalali()
{
    int gYear = this->Year() - 1600;
    int gMonth = this->Month() - 1;
    int gDay = this->Day() - 1;

    int gDayNo = 365*gYear + ((gYear+3)/4) - ((gYear+99)/100) + ((gYear+399)/400);

    for (int i=0; i < gMonth; ++i)
        gDayNo += jDaysInMonth[i];

    if (IsLeap(this->Year()) && gMonth>1 )
        ++gDayNo;

    gDayNo += gDay;

    int jDayNo = gDayNo - 79;

    int j_np = (jDayNo/ 12053);
    jDayNo %= 12053;

    int jYear = 979+ 33*j_np + 4*(jDayNo/1461);

    jDayNo %= 1461;

    if (jDayNo >= 366) {
        jYear += ((jDayNo-1)/ 365);
        jDayNo = (jDayNo-1)%365;
    }

    int i;
    for (i = 0; i < 11 && jDayNo >= jDaysInMonth[i]; ++i) {
        jDayNo -= jDaysInMonth[i];
    }
    int jMonth = i+1;
    int jDay = jDayNo+1;

    myJDay = jDay;
    myJMonth = jMonth;
    myJYear = jYear;
}

void Date::JalaliToGregorian()
{
    int jYear = this->Year(JALALI) - 979;
    int jMonth = this->Month(JALALI) - 1;
    int jDay = this->Day(JALALI) - 1;

    int jDayNo = 365*jYear + (jYear / 33)*8 + ((jYear%33+3) / 4);

    for (int i=0; i < jMonth; ++i)
        jDayNo += jDaysInMonth[i];

    jDayNo += jDay;

    int gDayNo = jDayNo + 79;

    int gYear = 1600 + 400 * (gDayNo / 146097);
    gDayNo = gDayNo % 146097;

    bool leap = true;
    if (gDayNo >= 36525) /* 36525 = 365*100 + 100/4 */
    {
        gDayNo--;
        gYear += 100*(gDayNo/36524);
        gDayNo = gDayNo % 36524;

        if (gDayNo >= 365)
            gDayNo++;
        else
            leap = false;
    }

    gYear += 4*(gDayNo/1461);
    gDayNo %= 1461;

    if (gDayNo >= 366) {
        leap = false;

        gDayNo--;
        gYear += (gDayNo/ 365);
        gDayNo = gDayNo % 365;
    }

    int i;
    for (i = 0; gDayNo >= gDaysInMonth[i] + (i == 1 && leap); i++)
        gDayNo -= gDaysInMonth[i] + (i == 1 && leap);
    int gMonth = i+1;
    int gDay = gDayNo+1;

    myGDay = gDay;
    myGMonth = gMonth;
    myGYear = gYear;
}

void Date::CheckDate(int m, int d, int y, DateType t)
{
    if(t == GREGORIAN)
    {
        if (m < 1 || 12 < m)              // month out of range?
        {
            m = 1;
        }
        myGMonth = m;

        if (d < 1 || DaysInMonth(m,y, GREGORIAN) < d)   // day out of range?
        {
            d = 1;
        }
        myGDay = d;
        myGYear = y;
        GregorianToJalali();
    }
    else
    {
        if( m < 1 || 12 < m)
        {
            m = 1;
        }
        myJMonth = m;
        if ( d < 1 || DaysInMonth(m, y, JALALI) < d)
        {
            d = 1;
        }
        myJDay = d;
        myJYear = y;
        JalaliToGregorian();
    }
}

bool Date::Equal(const Date & rhs) const
{
    return Absolute() == rhs.Absolute();
}

bool Date::Less(const Date & rhs) const
{
    return Absolute() < rhs.Absolute();
}


bool operator == (const Date & lhs, const Date & rhs)
{
    return lhs.Equal(rhs);
}

bool operator != (const Date & lhs, const Date & rhs)
{
    return ! (lhs == rhs);
}

bool operator <  (const Date & lhs, const Date & rhs)
{
    return lhs.Less(rhs);
}

bool operator >  (const Date & lhs, const Date & rhs)
{
    return rhs < lhs;
}

bool operator <= (const Date & lhs, const Date & rhs)
{
    return lhs == rhs || lhs < rhs;
}

bool operator >= (const Date & lhs, const Date & rhs)
{
    return rhs <= lhs;
}

#pragma once
#include "clsString.h"
#pragma warning(disable : 4996) // When You Use ctime Lib Should use this 

struct sDate
{
	unsigned short day = 0;
	unsigned short month = 0;
	unsigned short year = 0;
};
class clsDate
{
private:

	unsigned short _day = 1;
	unsigned short _month = 1;
	unsigned short _year = 1900;

	static unsigned short _GetYearNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_year + 1900;
	}

	static unsigned short _GetMonthNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_mon + 1;
	}

	static unsigned short _GetDayNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_mday;
	}
	static unsigned short _GetHourNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_hour;
	}
	static unsigned short _GetMinutesNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_min;
	}
	static unsigned short _GetSecondsNow()
	{
		time_t _time = time(0);
		return localtime(&_time)->tm_sec;
	}
public:
	clsDate()
	{
		*this = SystemDate();
	}

	clsDate(string dateString)
	{
		*this = StringToDate(dateString);
	}

	clsDate(short numberOfDayInyear, short year)
	{
		*this = GetDateFromDaysOrderInYear(numberOfDayInyear, year);
	}

	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	static string GetSystemDateTimeNow()
	{
		string systemDateTime = "";
		systemDateTime += clsDate::DateToString(SystemDate()) + " - ";
		systemDateTime += to_string(_GetHourNow()) + ":" + to_string(_GetMinutesNow()) + ":" + to_string(_GetSecondsNow());
		return systemDateTime;
	}

	void SetDay(short day)
	{
		_day = day;
	}
	short GetDay()
	{
		return _day;
	}
	_declspec(property(get = GetDay, put = SetDay)) short day;

	void SetMonth(short month)
	{
		_month = month;
	}
	short GetMonth()
	{
		return _month;
	}
	_declspec(property(get = GetMonth, put = SetMonth)) short month;

	void SetYear(short year)
	{
		_year = year;
	}
	short GetYear()
	{
		return _year;
	}
	_declspec(property(get = GetYear, put = SetYear)) short year;

	static clsDate SystemDate()
	{
		return clsDate(_GetDayNow(), _GetMonthNow(), _GetYearNow());
	}

	static clsDate StringToDate(string strDate)
	{
		vector <string> vDate = clsString::Split(strDate, "/");

		return clsDate(stoi(vDate[0]), stoi(vDate[1]), stoi(vDate[2]));
	}

	static bool IsLeapYear(short Year)
	{
		return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_year);
	}

	static bool IsValidDate(clsDate date)
	{
		return (date.month <= 12 && date.month >= 1) && (date.day <= NumberOfDaysInMonth(date.month, date.year));
	}
	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static short NumberOfDaysInMonth(short month, short year)
	{

		if (month < 1 || month > 12) return 0;

		short numberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return month == 2 ? (IsLeapYear(year) ? 29 : 28) : numberOfDays[month - 1];
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_month, _year);
	}

	static short NumberOfHoursInMonth(short month, short year)
	{
		return NumberOfDaysInMonth(month, year) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(this->month, this->year);
	}

	static int NumberOfMinutesInMonth(short month, short year)
	{
		return NumberOfHoursInMonth(month, year) * 60;
	}
	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(this->month, this->year);
	}

	static int NumberOfSecondsInMonth(short month, short year)
	{
		return NumberOfMinutesInMonth(month, year) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(this->month, this->year);
	}

	static int NumberOfDaysInYear(short year)
	{
		return IsLeapYear(year) ? 366 : 365;
	}
	int NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(this->year);
	}

	static int NumberOfHoursInYear(int year)
	{
		return NumberOfDaysInYear(year) * 24;
	}
	int NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(this->year);
	}

	static int NumberOfMinutesInYear(int year)
	{
		return NumberOfHoursInYear(year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(this->year);
	}

	static int NumberOfSecondsInYear(int Year)
	{
		return NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(this->year);
	}

	static short DayOfWeekOrder(short year, short month, short day)
	{
		int A = (14 - month) / 12;

		int Y = year - A;

		int M = month + (12 * A) - 2;

		int D = (day + Y + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * M) / 12)) % 7;

		return D;
	}
	static short DayOfWeekOrder(clsDate date)
	{
		return DayOfWeekOrder(date.year, date.month, date.day);
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}


	static string MonthShortName(short monthOrder)
	{
		string arrMonthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		if (monthOrder >= 1 && monthOrder <= 12) {
			return arrMonthNames[monthOrder - 1];
		}

		return "";
	}
	string MonthShortName()
	{
		return MonthShortName(this->month);
	}

	static string DateToString(clsDate date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}

	static bool IsLastDayInMonth(clsDate date)
	{
		return date.day == NumberOfDaysInMonth(date.month, date.year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short month)
	{
		return month == 12;
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_month);
	}

	static clsDate IncraseDateByOneDay(clsDate date) {
		if (IsLastDayInMonth(date)) {
			if (IsLastMonthInYear(date.month)) {
				date.day = 1;
				date.month = 1;
				date.year++;
			}
			else {
				date.day = 1;
				date.month++;
			}
		}
		else {
			date.day++;
		}

		return date;
	}
	clsDate IncraseDateByOneDay()
	{
		return IncraseDateByOneDay(*this);
	}

	static clsDate IncraseDateByXDays(int daysToAdd, clsDate date) {
		for (int i = 1; i <= daysToAdd; i++) {
			date = IncraseDateByOneDay(date);
		}
		return date;
	}
	clsDate IncraseDateByXDays(int daysToAdd)
	{
		return IncraseDateByXDays(daysToAdd, *this);
	}

	void AddDays(int daysToAdd)
	{
		*this = IncraseDateByXDays(daysToAdd);
	}

	static clsDate IncraseDateByOneWeek(clsDate date)
	{
		return IncraseDateByXDays(7, date);
	}
	clsDate IncraseDateByOneWeek()
	{
		return IncraseDateByOneWeek(*this);
	}

	static clsDate IncraseDateByXWeeks(int weeksToAdd, clsDate date)
	{
		for (int i = 1; i <= weeksToAdd; i++)
			date = IncraseDateByOneWeek(date);
		return date;
	}
	clsDate IncraseDateByXWeeks(int weeksToAdd)
	{
		return IncraseDateByXWeeks(weeksToAdd, *this);
	}

	void AddWeeks(int weeksToAdd)
	{
		*this = IncraseDateByXWeeks(weeksToAdd);
	}

	static clsDate IncraseDateByOneMonth(clsDate date) {

		if (IsLastMonthInYear(date.month)) {
			date.month = 1;
			date.year++;
		}
		else {
			date.month++;
		}

		short numberOfDaysInCurrentMonth = NumberOfDaysInMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth) {
			date.day = numberOfDaysInCurrentMonth;
		}
		return date;
	}
	clsDate IncraseDateByOneMonth()
	{
		return IncraseDateByOneMonth(*this);
	}


	static clsDate IncraseDateByXMonths(int monthsToAdd, clsDate date)
	{
		for (int i = 1; i <= monthsToAdd; i++)
			date = IncraseDateByOneMonth(date);
		return date;
	}
	clsDate IncraseDateByXMonths(int monthsToAdd)
	{
		return IncraseDateByXMonths(monthsToAdd, *this);
	}

	void AddMonths(int monthsToAdd)
	{
		*this = IncraseDateByXMonths(monthsToAdd);
	}

	static clsDate IncraseDateByOneYear(clsDate date)
	{
		date.year += 1;
		return date;
	}
	clsDate IncraseDateByOneYear()
	{
		return IncraseDateByOneYear(*this);
	}

	static clsDate IncraseDateByXYears(int yearsToAdd, clsDate date) {
		date.year += yearsToAdd;
		return date;
	}
	clsDate IncraseDateByXYears(int yearsToAdd)
	{
		return IncraseDateByXYears(yearsToAdd, *this);
	}

	void AddYears(short yearsToAdd)
	{
		_year += yearsToAdd;
	}

	static clsDate GetDateFromDaysOrderInYear(short daysOrderInYear, short year)
	{
		short remainingDays = daysOrderInYear;
		short monthDays = 0;

		clsDate date;
		date.SetMonth(1);
		date.SetYear(year);

		while (true)
		{
			monthDays = NumberOfDaysInMonth(date.month, year);

			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}

		return date;
	}

	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		return (date1.year < date2.year) ? true : ((date1.year == date2.year) ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
	}
	bool IsDateBefore(clsDate date)
	{
		return IsDate1BeforeDate2(*this, date);
	}

	static bool IsDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return (date1.year == date2.year) ? ((date1.month == date2.month) ? ((date1.day == date2.day) ? true : false) : false) : false;
	}
	bool IsDateEqual(clsDate date)
	{
		return IsDate1EqualDate2(*this, date);
	}

	static bool IsDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));
	}
	bool IsDateAfter(clsDate date)
	{
		return IsDate1AfterDate2(*this, date);
	}

	static int GetDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false) {
		int days = 0;

		while (IsDate1BeforeDate2(date1, date2)) {
			days++;
			date1 = IncraseDateByOneDay(date1);
		}

		return includeEndDay ? ++days : days;
	}
	int GetDifferenceInDays(clsDate date, bool includeEndDay = false)
	{
		return GetDifferenceInDays(*this, date, includeEndDay);
	}


	static void PrintMonthCalendar(short month, short year)
	{
		short current = DayOfWeekOrder(1, month, year);
		short numberOfDays = NumberOfDaysInMonth(month, year);

		printf("\n  _______________%s_______________\n\n",
			MonthShortName(month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (short j = 1; j <= numberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}

		}
	}
	void PrintMonthCalendar()
	{
		return PrintMonthCalendar(this->month, this->year);
	}

	static void PrintMonthDetails(short month, short year)
	{
		cout << "\nNumber Of Days    In Month [" << month << "] Is: "
			<< NumberOfDaysInMonth(month, year);
		cout << "\nNumber Of Hours   In Month [" << month << "] Is: "
			<< NumberOfHoursInMonth(month, year);
		cout << "\nNumber Of Minutes In Month [" << month << "] Is: "
			<< NumberOfMinutesInMonth(month, year);
		cout << "\nNumber Of Seconds In Month [" << month << "] Is: "
			<< NumberOfSecondsInMonth(month, year);
	}
	void PrintMonthDetails()
	{
		return PrintMonthDetails(this->year, this->month);
	}

	static void PrintYearCalendar(short year)
	{
		printf("\n  _________________________________\n\n");
		printf("\t Calendar - %d", year);
		printf("\n  _________________________________\n\n");

		for (int iMonth = 1; iMonth <= 12; iMonth++)
		{
			PrintMonthCalendar(iMonth, year);
		}
	}
	void PrintYearCalendar()
	{
		return PrintYearCalendar(this->year);
	}

	static short IsEndOfWeek(clsDate date)
	{
		return  DayOfWeekOrder(date.day, date.month, date.year) == 6;
	}
	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		//Weekends are Fri and Sat
		short dayIndex = DayOfWeekOrder(date.day, date.month, date.year);
		return  (dayIndex == 5 || dayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(date);

	}
	bool IsBusinessDay()
	{
		return  IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return 6 - DayOfWeekOrder(date.day, date.month, date.year);
	}
	short DaysUntilTheEndOfWeek()
	{
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date)
	{

		clsDate EndOfMonthDate;
		EndOfMonthDate.day = NumberOfDaysInMonth(date.month, date.year);
		EndOfMonthDate.month = date.month;
		EndOfMonthDate.year = date.year;

		return GetDifferenceInDays(date, EndOfMonthDate, true);

	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date)
	{

		clsDate EndOfYearDate;
		EndOfYearDate.day = 31;
		EndOfYearDate.month = 12;
		EndOfYearDate.year = date.year;

		return GetDifferenceInDays(date, EndOfYearDate, true);

	}
	short DaysUntilTheEndOfYear()
	{
		return  DaysUntilTheEndOfYear(*this);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate date1, clsDate date2)
	{
		if (IsDate1BeforeDate2(date1, date2))
		{
			return enDateCompare::Before;
		}
		else if (IsDate1EqualDate2(date1, date2))
		{
			return enDateCompare::Equal;
		}

		return enDateCompare::After;
		// return isDate1BeforeDate2(Date1, Date2) ? Before : ((isDate1AfterDate2(Date1, Date2)) ? After : Equal);
	}
	enDateCompare CompareDates(clsDate date2)
	{
		return CompareDates(*this, date2);
	}

	static void  SwapDates(clsDate& date1, clsDate& date2)
	{

		clsDate tempDate;
		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	void Print()
	{
		cout << DateToString() << endl;
	}
};
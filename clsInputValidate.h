#pragma once
#include "clsDate.h"
class clsInputValidate
{
public:

	// Overload IsNumberBetween Function For All Data Type and modifiers
	static bool IsNumberBetween(short number, short from, short to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(int number, int from, int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(unsigned int number, unsigned int from, unsigned int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(long int number, long int from, long int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(unsigned long int number, unsigned long int from, unsigned long int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(long long int number, long long int from, long long int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(unsigned long long int number, unsigned long long int from, unsigned long long int to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(double number, double from, double to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(long double number, long double from, long double to)
	{
		return number >= from && number <= to;
	}
	static bool IsNumberBetween(float number, float from, float to)
	{
		return number >= from && number <= to;
	}

	static bool IsDateBetween(clsDate date, clsDate date1, clsDate date2)
	{
		if (date.CompareDates(date1) == clsDate::Equal || date.CompareDates(date2) == clsDate::Equal)
		{
			return true;
		}

		if (date1.IsDateBefore(date2))
		{
			return date.CompareDates(date1) == clsDate::After && date.CompareDates(date2) == clsDate::Before;
		}
		else
		{
			return date.CompareDates(date2) == clsDate::After && date.CompareDates(date1) == clsDate::Before;
		}

	}

	static string ReadString()
	{
		string  str = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, str);
		return str;
	}

	static string ReadString(string message)
	{
		string  str = "";
		cout << message;
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, str);
		return str;
	}

	static int ReadIntNumber(string errorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return Number;
	}

	static double ReadDoubleNumber(string errorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string errorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return Number;
	}

	static int ReadIntBetween(int from, int to, string errorMessage = "Number is not within range, Enter again:\n")
	{
		int number = ReadIntNumber();
		while (!IsNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = ReadIntNumber();
		}
		return number;
	}


	static double ReadDoubleBetween(double from, double to, string errorMessage = "Number is not within range, Enter again:\n")
	{
		double number = ReadDoubleNumber();
		while (!IsNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = ReadDoubleNumber();
		}
		return number;
	}

	static float ReadDoubleBetween(float from, float to, string errorMessage = "Number is not within range, Enter again:\n")
	{
		float number = ReadFloatNumber();
		while (!IsNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = ReadFloatNumber();
		}
		return number;
	}
};


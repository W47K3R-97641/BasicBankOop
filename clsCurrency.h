#pragma once
#include "clsString.h"

using namespace std;
class clsCurrency
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1};
	enMode _mode;
	string _country;
	string _currencyCode;
	string _currencyName;
	float _rate;

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static clsCurrency _ConvertLinetoCurrencyObject(string line, string seperator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(line, seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyToLine(clsCurrency currency, string seperator = "#//#")
	{
		string recordLine = "";

		recordLine += currency.country + seperator;
		recordLine += currency.currencyCode + seperator;
		recordLine += currency.currencyName + seperator;
		recordLine += to_string(currency.Rate());

		return recordLine;
	}
	
	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream myFile;
		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";

			while (getline(myFile, line))
			{
				clsCurrency currency = _ConvertLinetoCurrencyObject(line);
				vCurrencies.push_back(currency);
			}

			myFile.close();
		}
		return vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream myFile;

		myFile.open("Currencies.txt", ios::out);

		if (myFile.is_open())
		{
			for (clsCurrency currency : vCurrencies)
			{
				string dataLine = _ConvertCurrencyToLine(currency);
				myFile << dataLine << endl;
			}
			myFile.close();
		}
	}
	
	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& currency : vCurrencies)
		{
			if (currency.currencyName == currencyName)
			{
				currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrencies);
	}
public:

	clsCurrency(enMode mode, string country, string currencyCode, string currencyName, float rate)
	{
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_country = country;
		_rate = rate;
		_mode = mode;
	}

	string Country()
	{
		return _country;
	}
	_declspec(property(get = Country)) string country;

	string CurrencyName()
	{
		return _currencyName;
	}
	_declspec(property(get = CurrencyName)) string currencyName;

	string CurrencyCode()
	{
		return _currencyCode;
	}
	_declspec(property(get = CurrencyCode)) string currencyCode;

	float Rate()
	{
		return _rate;
	}
	void UpdateRate(float newRate)
	{
		_rate = newRate;
		_Update();
	}
	
	bool IsEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	static clsCurrency FindByCode(string currencyCode)
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		currencyCode = clsString::UpperAllString(currencyCode);

		for (clsCurrency currency : vCurrencies)
		{
			if (clsString::UpperAllString(currency.currencyCode) == currencyCode)
			{
				return currency;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string country)
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		
		country = clsString::UpperAllString(country);

		for (clsCurrency currency : vCurrencies)
		{
			if (clsString::UpperAllString(currency.country) == country)
			{
				return currency;
			}
		}
		
		return _GetEmptyCurrencyObject();
	}
	
	static bool IsCurrencyExist(string currencyCode)
	{
		return !(FindByCode(currencyCode).IsEmpty());
	}
	
	static bool IsCurrencyExist(clsCurrency currency)
	{
		return !currency.IsEmpty();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}
	
	double ConvertToUSD(double amount)
	{
		return amount / Rate();
	}

	double ConvertToAnotherCurrency(double amount, clsCurrency currencyTo)
	{
		double amountInUSD = ConvertToUSD(amount);

		if (currencyTo.currencyCode == "USD")
		{
			return amountInUSD;
		}
		return amountInUSD * currencyTo.Rate();
	}
};


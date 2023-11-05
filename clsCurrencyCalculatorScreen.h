#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{

	static void _PrintCurrencyCard(clsCurrency currency, string Title = "Currency Card:")
	{
		cout << "\n" << Title << "\n";
		cout << "_______________________________";
		cout << "\n Country    : " << currency.country;
		cout << "\n Code       : " << currency.currencyCode;
		cout << "\n Name       : " << currency.currencyName;
		cout << "\n Rate(1$)   : " << currency.Rate();
		cout << "\n_______________________________\n\n";
	}

	static clsCurrency _GetCurrency(string message)
	{
		
		string currencyCode = clsInputValidate::ReadString(message);
		clsCurrency currency = clsCurrency::FindByCode(currencyCode);
		
		while (!clsCurrency::IsCurrencyExist(currency))
		{
			cout << "\nCurrency is not found, choose another one: ";
			currencyCode = clsInputValidate::ReadString(message);
			currency = clsCurrency::FindByCode(currencyCode);
		}

		return currency;
	}

	static double _ReadAmount()
	{
		cout << "\nEnter Amount To Exchange : ";
		double amount = clsInputValidate::ReadDoubleNumber();
		return amount;
	}

	static void _PrintCalculationsResults(double amount, clsCurrency currencyFrom, clsCurrency currencyTo)
	{
		_PrintCurrencyCard(currencyFrom, "Convert From:");

		double amountInUSD = currencyFrom.ConvertToUSD(amount);

		cout << amount << " " << currencyFrom.currencyCode
			 << " = " << amountInUSD << " USD\n";

		if (currencyTo.currencyCode == "USD")
			return;

		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(currencyTo, "Convert To:");

		double amountInCurrencyTo = currencyFrom.ConvertToAnotherCurrency(amount, currencyTo);
		
		cout << amount << " " << currencyFrom.CurrencyCode()
			<< " = " << amountInCurrencyTo << " " << currencyTo.CurrencyCode();
	
	}
public:
	static void ShowCurrencyCalculatorScreen()
	{
		do
		{
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency currencyFrom = _GetCurrency("\nEnter Currency 1 Code : ");
			clsCurrency currencyTo   = _GetCurrency("\nEnter Currency 2 Code : ");

			double amount = _ReadAmount();

			_PrintCalculationsResults(amount, currencyFrom, currencyTo);

		} while (clsUtil::Confirm("\n\nDo you want to perform another calculation ?"));
	}

};


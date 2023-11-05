#pragma once
#include "clsScreen.h" 
#include "clsCurrency.h"
class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyDetails(clsCurrency currency)
	{
		cout << "\n\t";
		cout << "| " << setw(30) << left << currency.country;
		cout << "| " << setw(10) << left << currency.currencyCode;
		cout << "| " << setw(40) << left << currency.currencyName;
		cout << "| " << setw(24) << left << currency.Rate();
		
	}
public:
	void static ShowCurrenciesListScreen()
	{
		system("cls");

		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string title = "\tList Currencies Screen";
		string subTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";
		
		_DrawScreenHeader(title, subTitle);

		cout << "\t_________________________________________________________________________________________________________\n\t";
		cout << "| " << setw(30) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(24) << left << "Rate/(1$)";
		cout << "\n\t_________________________________________________________________________________________________________\n";

		if (vCurrencies.size() == 0)
			cout << "\t\t\t\tNo Currencies Available In the System!";
		else
		{
			for (clsCurrency currency : vCurrencies)
			{
				_PrintCurrencyDetails(currency);
			}
		}
		cout << "\n\t_________________________________________________________________________________________________________\n";
	}
};


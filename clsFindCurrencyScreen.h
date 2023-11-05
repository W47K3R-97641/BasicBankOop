#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFindBy {Code = 1, Country = 2};

	static enFindBy _ReadFindByOption()
	{
		cout << setw(37) << left << "" << "Find By : [1] Code [2] Country ? ";

		enFindBy choice = (enFindBy)clsInputValidate::ReadIntBetween(1, 2, "Invalid Option\nFind By : [1] Code [2] Country ?");
		
		return choice;
	}

	static void _ShowResult(clsCurrency currency)
	{
		if (currency.IsEmpty())
		{
			cout << "\nCurrency Not Found :(";
		}
		else
		{
			cout << "\nCurrency Found :(";

			_PrintCurrencyCard(currency);
		}
	}

	static void _PrintCurrencyCard(clsCurrency currency)
	{
		cout << "\n_______________________________";
		cout << "\n Country    : " << currency.country;
		cout << "\n Code       : " << currency.currencyCode;
		cout << "\n Name       : " << currency.currencyName;
		cout << "\n Rate(1$)   : " << currency.Rate();
		cout << "\n_______________________________";
	}
public:
	static void ShowFindCurrencyScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tFind Currency Screen");

		clsCurrency currency = clsCurrency::FindByCode("");
		
		switch (_ReadFindByOption())
		{
		case enFindBy::Code: 
		{
			string currencyCode = clsInputValidate::ReadString("\nEnter Currency Code : ");
			currency = clsCurrency::FindByCode(currencyCode);
			break;
		}
		case enFindBy::Country:
		{
			string country = clsInputValidate::ReadString("\nEnter Country : ");
			currency = clsCurrency::FindByCountry(country);
			break;
		}
		}

		_ShowResult(currency);

	}
	
};


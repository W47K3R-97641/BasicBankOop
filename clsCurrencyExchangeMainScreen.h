#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
	enum enCurrenciesMenueOptions {
		eListCurrencies = 1, eFindCurrency = 2,
		eUpdateRate = 3, eCurrencyCalculator = 4,
		eMainMenue = 5
	};

	static enCurrenciesMenueOptions _ReadCurrenciesMainMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";

		enCurrenciesMenueOptions choice = (enCurrenciesMenueOptions)clsInputValidate::ReadIntBetween(1, 5, "Enter Number between 1 to 5?");
		return choice;
	}

	static void _GoBackToCurrenciesMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Menue...\n";
		system("pause>0");
		ShowMainCurrenciesMenue();
	}

	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMenueOption(enCurrenciesMenueOptions currenciesMenueOption)
	{
		system("cls");
		switch (currenciesMenueOption)
		{
		case enCurrenciesMenueOptions::eListCurrencies:
			_ShowListCurrenciesScreen();
			_GoBackToCurrenciesMenue();
			break;
		case enCurrenciesMenueOptions::eFindCurrency:
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenue();
			break;
		case enCurrenciesMenueOptions::eUpdateRate:
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenue();
			break;
		case enCurrenciesMenueOptions::eCurrencyCalculator:
			_ShowCurrencyCalculatorScreen();
			ShowMainCurrenciesMenue();
			break;
		case enCurrenciesMenueOptions::eMainMenue:
			break;
		}
	}
public:
	static void ShowMainCurrenciesMenue()
	{
		system("cls");

		_DrawScreenHeader("    Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformCurrenciesMenueOption(_ReadCurrenciesMainMenueOptions());
	}
};


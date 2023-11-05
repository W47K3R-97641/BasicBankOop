#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsManageUsers.h"
#include "clsCurrencyExchangeMainScreen.h"

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2,
		eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eLoginRegister = 8,  
		eCurrncyExchange = 9, eExit = 10
	};

	static enMainMenueOptions _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";

		enMainMenueOptions choice = (enMainMenueOptions)clsInputValidate::ReadIntBetween(1, 10, "Enter Number between 1 to 10?");
		return choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientsScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsersMenue::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowMainCurrenciesMenue();
	}

	static void _Logout()
	{
		currentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOptions mainMenueOption)
	{
		system("cls");
		switch (mainMenueOption)
		{
		case enMainMenueOptions::eListClients:
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eAddNewClient:
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eDeleteClient:
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eUpdateClient:
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eFindClient:
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eShowTransactionsMenue:
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eManageUsers:
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eLoginRegister:
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eCurrncyExchange:
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eExit:
			_Logout();
			break;
		}

	}
public:
	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Menue");
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformMainMenueOption(_ReadMainMenueOption());
	}
};



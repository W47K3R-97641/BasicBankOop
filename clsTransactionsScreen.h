#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferRegisterScreen.h"
class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenueOptions {
		eDeposit       = 1, eWithdraw = 2,
		eTotalBalances = 3, eTransfer = 4,
		eTransferLog   = 5,	eShowMainMenue = 6,
	};

	static enTransactionsMenueOptions _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";

		enTransactionsMenueOptions choice = (enTransactionsMenueOptions)clsInputValidate::ReadIntBetween(1, 6, "Enter Number between 1 to 6?");
		return choice;
	}
	
	static void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWitdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferRegisterScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions transactionsMenueOption)
	{
		system("cls");
		switch (transactionsMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eWithdraw:
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eTotalBalances:
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eTransfer:
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eTransferLog:
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eShowMainMenue:
			//do nothing here the main screen will handle it :-) ;
			break;
		}
	}


public:

	static void ShowTransactionsMenue()
	{
		if (!_CheckAccessRight(clsUser::enPermissions::pTransactions))
			return;

		system("cls");
		_DrawScreenHeader("\t\tTransactions Menue");


		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformTransactionsMenueOption(_ReadTransactionsMenueOption());
	}
};


#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nAcc. Number : " << client.accountNumber;
		cout << "\nBalance     : " << client.accountBalance;
		cout << "\n___________________\n";
	}
	static string _ReadAccountNumber()
	{
		cout << "\nPlease Enter Account Number to Transfer From: ";
		string accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		return accountNumber;
	}

	static double _ReadAmount(clsBankClient sourceClient)
	{
		double amount;

		cout << "\nEnter Transfer Amount? ";

		amount = clsInputValidate::ReadDoubleNumber();

		while (amount > sourceClient.accountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			amount = clsInputValidate::ReadDoubleNumber();
		}

		return amount;
	}

public:
	static void ShowTransferScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tTransfer Screen");

		clsBankClient sourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(sourceClient);

		clsBankClient destinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(destinationClient);

		double amount = _ReadAmount(sourceClient);

		if (clsUtil::Confirm("\nAre you sure you want to perform this operation ? "))
		{
			if (sourceClient.Transfer(amount, destinationClient))
			{
				cout << "\n Transfer done Successfully :)\n";
			}
			else
			{
				cout << "\n Transfer Faild :(\n";

			}
		}

		_PrintClient(sourceClient);
		_PrintClient(destinationClient);	
	}
};


#pragma once
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsWithdrawScreen : protected clsScreen
{
	static double _ReadAmount()
	{
		double amount = 0;
		cout << "\nPlease enter withdraw amount? ";
		cin >> amount;
		return amount;
	}

	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << client.firstName;
		cout << "\nLastName    : " << client.lastName;
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nEmail       : " << client.email;
		cout << "\nPhone       : " << client.phone;
		cout << "\nAcc. Number : " << client.accountNumber;
		cout << "\nPassword    : " << client.pinCode;
		cout << "\nBalance     : " << client.accountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber()
	{
		cout << "\nPlease Enter Account Number: ";
		string accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		return accountNumber;
	}
public:
	static void ShowWitdrawScreen()
	{

		_DrawScreenHeader("\t  Deposit Screen");

		clsBankClient client = clsBankClient::Find(_ReadAccountNumber());
		
		_PrintClient(client);

		double amount = _ReadAmount();

		if (clsUtil::Confirm("\nAre you sure you want to perform this transaction? "))
		{
			if (client.Withdraw(amount))
			{
				cout << "\nAmount Deposited Successfully.\n";
				cout << "\nNew Balance Is: " << client.accountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << amount;
				cout << "\nYour Balance is: " << client.accountBalance;
			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};
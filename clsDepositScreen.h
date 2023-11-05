#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"


class clsDepositScreen : protected clsScreen
{
private:
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

	static double _ReadAmount()
	{
		double amount = 0;
		cout << "\nPlease enter deposit amount? ";
		amount = clsInputValidate::ReadDoubleNumber();
		return amount;
	}
public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t  Deposit Screen");

		string accountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "\nClient with [" << accountNumber << "] does not exist";
			accountNumber = _ReadAccountNumber();
		}

		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);

		double amount = _ReadAmount();

		if (clsUtil::Confirm("\nAre you sure you want to perform this transaction? "))
		{
			client.Deposit(amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << client.accountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}

};

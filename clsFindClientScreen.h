#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsFindClientsScreen : protected clsScreen
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
public:
	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRight(clsUser::enPermissions::pFindClient))
			return;

		_DrawScreenHeader("\t  Find Client Screen");

		cout << "\nPlease Enter Account Number: ";
		string accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accountNumber);

		if (!client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
			_PrintClient(client);
		}
		else
		{
			cout << "\nClient Was not Found :-(\n";
		}

	}
};
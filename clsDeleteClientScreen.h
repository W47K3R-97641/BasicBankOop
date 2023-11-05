#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsDeleteClientScreen : protected clsScreen
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
    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRight(clsUser::enPermissions::pDeleteClient))
            return;

        _DrawScreenHeader("\t  Delete Client Screen");

        cout << "\nPlease enter client account number :";
        string accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, choose another one : ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);

        cout << "\nDelete Client:\n";
        cout << "\n____________________\n";
        _PrintClient(client);

        if (clsUtil::Confirm("\nAre you sure you want to delete this client ?"))
        {
            if (client.Delete())
                cout << "\nClient Deleted Successfully :-)";
            else
                cout << "\nError Client Was not Deleted\n";
        }
        else
        {
            cout << "\nClient deletion has been cancelled";
        }
    }
};




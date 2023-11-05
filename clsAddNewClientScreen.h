#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& client)
    {
        cout << "\nEnter FirstName:";
        client.firstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName:";
        client.lastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        client.email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        client.phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        client.pinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        client.accountBalance = clsInputValidate::ReadFloatNumber();

    }

    static void _PrintClientCard(clsBankClient client)
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
    static void ShowAddNewClientScreen()
    {
        if (!_CheckAccessRight(clsUser::enPermissions::pAddNewClient))
            return;

        _DrawScreenHeader("\t  Add New Client Screen");

        cout << "\nPlease enter client account number :";
        string accountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(accountNumber))
        {
            cout << "\nAccount number is already used, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient newClient = clsBankClient::GetAddNewClientObject(accountNumber);

        _ReadClientInfo(newClient);

        clsBankClient::enSaveResults saveResult = newClient.Save();

        switch (saveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Added successfully :-)\n";
            _PrintClientCard(newClient);
            break;
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        case clsBankClient::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
    }
};


